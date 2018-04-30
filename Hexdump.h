#ifndef __HEXDUMP_H__
#define __HEXDUMP_H__

#include <sstream>
#include <iterator>
#include <iomanip>
#include <cctype>

template<typename T>
void hexdump(const T& data, size_t len)
{
	std::stringstream hexSs;
	std::stringstream ss;
	int addr = 0;
	int c = 0;

	std::cout << "HexDump(" << len << ") bytes\n";
	for (auto i = 0U; i < len; i++)
	{
		switch (c)
		{
		case 4:
		case 12:
			hexSs << ' ';
			break;
		case 8:
			hexSs << " -";
			break;
		case 16:
			std::cout << std::right << std::setfill('0') << std::setw(8)
				<< std::hex << (int) addr << " * ";
			std::cout << std::left << std::setfill(' ') << std::setw(78)
				<< hexSs.str() << " | " << ss.str() << "\n";

			addr += i;
			c = 0;

			hexSs.str("");
			hexSs.clear();

			ss.str("");
			ss.clear();
			break;
		}		

		c++;

		if (c > 1) hexSs << ' ';

		hexSs << std::setfill('0') << std::setw(2) << std::hex << (int) data[i];
		ss << static_cast<char>(std::isprint(data[i]) ? data[i] : '.');
	}

	if (hexSs.tellp() > 0)
	{
		std::cout << std::right << std::setfill('0') << std::setw(8)
			<< std::hex << (int) addr << " * ";
		std::cout << std::left << std::setfill(' ') << std::setw(78)
			<< hexSs.str() << " | " << ss.str() << "\n";
	}
}

#endif /* __HEXDUMP_H__ */

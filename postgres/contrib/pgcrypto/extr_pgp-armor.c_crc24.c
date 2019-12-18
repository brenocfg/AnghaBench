#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;

/* Variables and functions */
 unsigned int CRC24_INIT ; 
 unsigned int CRC24_POLY ; 

__attribute__((used)) static long
crc24(const uint8 *data, unsigned len)
{
	unsigned	crc = CRC24_INIT;
	int			i;

	while (len--)
	{
		crc ^= (*data++) << 16;
		for (i = 0; i < 8; i++)
		{
			crc <<= 1;
			if (crc & 0x1000000)
				crc ^= CRC24_POLY;
		}
	}
	return crc & 0xffffffL;
}
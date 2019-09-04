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
typedef  int uint64_t ;

/* Variables and functions */
 int CRC64_ECMA182_POLY ; 
 int* crc64_table ; 

__attribute__((used)) static void generate_crc64_table(void)
{
	uint64_t i, j, c, crc;

	for (i = 0; i < 256; i++) {
		crc = 0;
		c = i << 56;

		for (j = 0; j < 8; j++) {
			if ((crc ^ c) & 0x8000000000000000ULL)
				crc = (crc << 1) ^ CRC64_ECMA182_POLY;
			else
				crc <<= 1;
			c <<= 1;
		}

		crc64_table[i] = crc;
	}
}
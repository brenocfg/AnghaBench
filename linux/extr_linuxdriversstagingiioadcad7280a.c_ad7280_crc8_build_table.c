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

/* Variables and functions */
 unsigned char HIGHBIT ; 
 unsigned char POLYNOM ; 

__attribute__((used)) static void ad7280_crc8_build_table(unsigned char *crc_tab)
{
	unsigned char bit, crc;
	int cnt, i;

	for (cnt = 0; cnt < 256; cnt++) {
		crc = cnt;
		for (i = 0; i < 8; i++) {
			bit = crc & HIGHBIT;
			crc <<= 1;
			if (bit)
				crc ^= POLYNOM;
		}
		crc_tab[cnt] = crc;
	}
}
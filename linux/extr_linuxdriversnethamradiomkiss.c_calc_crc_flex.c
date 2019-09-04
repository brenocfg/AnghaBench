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
 unsigned short* crc_flex_table ; 

__attribute__((used)) static unsigned short calc_crc_flex(unsigned char *cp, int size)
{
	unsigned short crc = 0xffff;

	while (size--)
		crc = (crc << 8) ^ crc_flex_table[((crc >> 8) ^ *cp++) & 0xff];

	return crc;
}
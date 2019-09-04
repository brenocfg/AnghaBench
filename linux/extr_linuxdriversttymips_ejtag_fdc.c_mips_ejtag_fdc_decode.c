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
typedef  char u8 ;
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static unsigned int mips_ejtag_fdc_decode(u32 word, char *buf)
{
	buf[0] = (u8)word;
	word >>= 8;
	if (word == 0x808080)
		return 1;
	buf[1] = (u8)word;
	word >>= 8;
	if (word == 0x8181)
		return 2;
	buf[2] = (u8)word;
	word >>= 8;
	if (word == 0x82)
		return 3;
	buf[3] = (u8)word;
	return 4;
}
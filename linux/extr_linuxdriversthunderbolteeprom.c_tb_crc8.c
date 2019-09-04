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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static u8 tb_crc8(u8 *data, int len)
{
	int i, j;
	u8 val = 0xff;
	for (i = 0; i < len; i++) {
		val ^= data[i];
		for (j = 0; j < 8; j++)
			val = (val << 1) ^ ((val & 0x80) ? 7 : 0);
	}
	return val;
}
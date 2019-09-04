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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static u16 lan78xx_wakeframe_crc16(const u8 *buf, int len)
{
	const u16 crc16poly = 0x8005;
	int i;
	u16 bit, crc, msb;
	u8 data;

	crc = 0xFFFF;
	for (i = 0; i < len; i++) {
		data = *buf++;
		for (bit = 0; bit < 8; bit++) {
			msb = crc >> 15;
			crc <<= 1;

			if (msb ^ (u16)(data & 1)) {
				crc ^= crc16poly;
				crc |= (u16)0x0001U;
			}
			data >>= 1;
		}
	}

	return crc;
}
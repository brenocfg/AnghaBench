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

__attribute__((used)) static void swap_packet_bitfield_from_le(unsigned char *data)
{
#ifdef __BIG_ENDIAN_BITFIELD
	unsigned char tmp = *data, ret = 0;

	/*
	 * transform bits from ccc.bbb.aa to aa.bbb.ccc
	 */
	ret |= (tmp & 0xe0) >> 5;
	ret |= (tmp & 0x1c) << 1;
	ret |= (tmp & 0x03) << 6;
	*data = ret & 0xff;
#endif
}
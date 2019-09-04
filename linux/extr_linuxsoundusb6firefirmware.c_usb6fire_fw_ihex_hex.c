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
 int hex_to_bin (int const) ; 

__attribute__((used)) static u8 usb6fire_fw_ihex_hex(const u8 *data, u8 *crc)
{
	u8 val = 0;
	int hval;

	hval = hex_to_bin(data[0]);
	if (hval >= 0)
		val |= (hval << 4);

	hval = hex_to_bin(data[1]);
	if (hval >= 0)
		val |= hval;

	*crc += val;
	return val;
}
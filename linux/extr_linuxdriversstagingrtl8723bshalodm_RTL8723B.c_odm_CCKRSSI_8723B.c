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
typedef  int s8 ;

/* Variables and functions */

s8 odm_CCKRSSI_8723B(u8 LNA_idx, u8 VGA_idx)
{
	s8 rx_pwr_all = 0x00;

	switch (LNA_idx) {
	/* 46  53 73 95 201301231630 */
	/*  46 53 77 99 201301241630 */

	case 6:
		rx_pwr_all = -34 - (2 * VGA_idx);
		break;
	case 4:
		rx_pwr_all = -14 - (2 * VGA_idx);
		break;
	case 1:
		rx_pwr_all = 6 - (2 * VGA_idx);
		break;
	case 0:
		rx_pwr_all = 16 - (2 * VGA_idx);
		break;
	default:
		/* rx_pwr_all = -53+(2*(31-VGA_idx)); */
		/* DbgPrint("wrong LNA index\n"); */
		break;

	}
	return rx_pwr_all;
}
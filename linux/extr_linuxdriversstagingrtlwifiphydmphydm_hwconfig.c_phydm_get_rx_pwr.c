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

__attribute__((used)) static inline s8 phydm_get_rx_pwr(u8 LNA_idx, u8 VGA_idx, u8 cck_highpwr)
{
	switch (LNA_idx) {
	case 7:
		if (VGA_idx <= 27)
			return -100 + 2 * (27 - VGA_idx); /*VGA_idx = 27~2*/
		else
			return -100;
		break;
	case 6:
		return -48 + 2 * (2 - VGA_idx); /*VGA_idx = 2~0*/
	case 5:
		return -42 + 2 * (7 - VGA_idx); /*VGA_idx = 7~5*/
	case 4:
		return -36 + 2 * (7 - VGA_idx); /*VGA_idx = 7~4*/
	case 3:
		return -24 + 2 * (7 - VGA_idx); /*VGA_idx = 7~0*/
	case 2:
		if (cck_highpwr)
			return -12 + 2 * (5 - VGA_idx); /*VGA_idx = 5~0*/
		else
			return -6 + 2 * (5 - VGA_idx);
		break;
	case 1:
		return 8 - 2 * VGA_idx;
	case 0:
		return 14 - 2 * VGA_idx;
	default:
		break;
	}
	return 0;
}
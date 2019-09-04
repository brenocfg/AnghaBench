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

bool rtw_is_cckratesonly_included(u8 *rate)
{
	while (*rate) {
		u8 r = *rate & 0x7f;

		if (r != 2 && r != 4 && r != 11 && r != 22)
			return false;
		rate++;
	}

	return true;
}
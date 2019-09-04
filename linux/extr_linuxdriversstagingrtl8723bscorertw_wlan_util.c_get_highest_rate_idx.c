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
typedef  int u32 ;

/* Variables and functions */
 int BIT (int) ; 

unsigned char get_highest_rate_idx(u32 mask)
{
	int i;
	unsigned char rate_idx = 0;

	for (i = 31; i >= 0; i--) {
		if (mask & BIT(i)) {
			rate_idx = i;
			break;
		}
	}

	return rate_idx;
}
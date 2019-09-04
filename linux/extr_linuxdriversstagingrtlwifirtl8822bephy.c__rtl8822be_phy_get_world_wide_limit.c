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
typedef  size_t u8 ;

/* Variables and functions */
 size_t MAX_REGULATION_NUM ; 

__attribute__((used)) static char _rtl8822be_phy_get_world_wide_limit(char *limit_table)
{
	char min = limit_table[0];
	u8 i = 0;

	for (i = 0; i < MAX_REGULATION_NUM; ++i) {
		if (limit_table[i] < min)
			min = limit_table[i];
	}
	return min;
}
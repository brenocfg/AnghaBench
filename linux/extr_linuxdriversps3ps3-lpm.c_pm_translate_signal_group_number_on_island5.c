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
typedef  int u64 ;

/* Variables and functions */
 int PM_ISLAND5_BASE_SIGNAL_GROUP_NUMBER ; 

__attribute__((used)) static u64 pm_translate_signal_group_number_on_island5(u64 subgroup)
{

	switch (subgroup) {
	case 3:
		subgroup = 4;
		break;
	case 4:
		subgroup = 6;
		break;
	default:
		break;
	}
	return PM_ISLAND5_BASE_SIGNAL_GROUP_NUMBER + subgroup;
}
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
typedef  enum rw_hint { ____Placeholder_rw_hint } rw_hint ;

/* Variables and functions */
 int CURSEG_COLD_DATA ; 
 int CURSEG_HOT_DATA ; 
 int CURSEG_WARM_DATA ; 
#define  WRITE_LIFE_EXTREME 129 
#define  WRITE_LIFE_SHORT 128 

int f2fs_rw_hint_to_seg_type(enum rw_hint hint)
{
	switch (hint) {
	case WRITE_LIFE_SHORT:
		return CURSEG_HOT_DATA;
	case WRITE_LIFE_EXTREME:
		return CURSEG_COLD_DATA;
	default:
		return CURSEG_WARM_DATA;
	}
}
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
#define  RWF_WRITE_LIFE_NOT_SET 133 
#define  RWH_WRITE_LIFE_EXTREME 132 
#define  RWH_WRITE_LIFE_LONG 131 
#define  RWH_WRITE_LIFE_MEDIUM 130 
#define  RWH_WRITE_LIFE_NONE 129 
#define  RWH_WRITE_LIFE_SHORT 128 

__attribute__((used)) static bool rw_hint_valid(enum rw_hint hint)
{
	switch (hint) {
	case RWF_WRITE_LIFE_NOT_SET:
	case RWH_WRITE_LIFE_NONE:
	case RWH_WRITE_LIFE_SHORT:
	case RWH_WRITE_LIFE_MEDIUM:
	case RWH_WRITE_LIFE_LONG:
	case RWH_WRITE_LIFE_EXTREME:
		return true;
	default:
		return false;
	}
}
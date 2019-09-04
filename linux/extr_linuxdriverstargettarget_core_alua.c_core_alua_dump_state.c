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
#define  ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED 134 
#define  ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED 133 
#define  ALUA_ACCESS_STATE_LBA_DEPENDENT 132 
#define  ALUA_ACCESS_STATE_OFFLINE 131 
#define  ALUA_ACCESS_STATE_STANDBY 130 
#define  ALUA_ACCESS_STATE_TRANSITION 129 
#define  ALUA_ACCESS_STATE_UNAVAILABLE 128 

__attribute__((used)) static char *core_alua_dump_state(int state)
{
	switch (state) {
	case ALUA_ACCESS_STATE_ACTIVE_OPTIMIZED:
		return "Active/Optimized";
	case ALUA_ACCESS_STATE_ACTIVE_NON_OPTIMIZED:
		return "Active/NonOptimized";
	case ALUA_ACCESS_STATE_LBA_DEPENDENT:
		return "LBA Dependent";
	case ALUA_ACCESS_STATE_STANDBY:
		return "Standby";
	case ALUA_ACCESS_STATE_UNAVAILABLE:
		return "Unavailable";
	case ALUA_ACCESS_STATE_OFFLINE:
		return "Offline";
	case ALUA_ACCESS_STATE_TRANSITION:
		return "Transitioning";
	default:
		return "Unknown";
	}

	return NULL;
}
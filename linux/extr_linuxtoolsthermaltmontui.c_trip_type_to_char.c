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
#define  THERMAL_TRIP_ACTIVE 131 
#define  THERMAL_TRIP_CRITICAL 130 
#define  THERMAL_TRIP_HOT 129 
#define  THERMAL_TRIP_PASSIVE 128 

__attribute__((used)) static char trip_type_to_char(int type)
{
	switch (type) {
	case THERMAL_TRIP_CRITICAL: return 'C';
	case THERMAL_TRIP_HOT: return 'H';
	case THERMAL_TRIP_PASSIVE: return 'P';
	case THERMAL_TRIP_ACTIVE: return 'A';
	default:
		return '?';
	}
}
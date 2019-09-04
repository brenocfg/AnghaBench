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
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_1000baseT_Half ; 
 int ADVERTISE_FIBER_1000FULL ; 
 int ADVERTISE_FIBER_1000HALF ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_ASYM_FIBER ; 
 int ADVERTISE_PAUSE_CAP ; 
 int ADVERTISE_PAUSE_FIBER ; 
 int LPA_PAUSE_ASYM_FIBER ; 

__attribute__((used)) static inline u32 ethtool_adv_to_fiber_adv_t(u32 ethadv)
{
	u32 result = 0;

	if (ethadv & ADVERTISED_1000baseT_Half)
		result |= ADVERTISE_FIBER_1000HALF;
	if (ethadv & ADVERTISED_1000baseT_Full)
		result |= ADVERTISE_FIBER_1000FULL;

	if ((ethadv & ADVERTISE_PAUSE_ASYM) && (ethadv & ADVERTISE_PAUSE_CAP))
		result |= LPA_PAUSE_ASYM_FIBER;
	else if (ethadv & ADVERTISE_PAUSE_CAP)
		result |= (ADVERTISE_PAUSE_FIBER
			   & (~ADVERTISE_PAUSE_ASYM_FIBER));

	return result;
}
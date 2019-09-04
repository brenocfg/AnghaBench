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
 int LPA_FIBER_1000FULL ; 
 int LPA_FIBER_1000HALF ; 

__attribute__((used)) static u32 fiber_lpa_to_ethtool_lpa_t(u32 lpa)
{
	u32 result = 0;

	if (lpa & LPA_FIBER_1000HALF)
		result |= ADVERTISED_1000baseT_Half;
	if (lpa & LPA_FIBER_1000FULL)
		result |= ADVERTISED_1000baseT_Full;

	return result;
}
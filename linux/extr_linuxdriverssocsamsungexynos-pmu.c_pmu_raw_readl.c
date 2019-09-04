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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ pmu_base_addr ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 

u32 pmu_raw_readl(u32 offset)
{
	return readl_relaxed(pmu_base_addr + offset);
}
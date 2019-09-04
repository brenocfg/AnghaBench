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
struct hisi_pmu {int base; } ;

/* Variables and functions */
 int L3C_EVENT_TYPE0 ; 
 int L3C_EVTYPE_NONE ; 
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void hisi_l3c_pmu_write_evtype(struct hisi_pmu *l3c_pmu, int idx,
				      u32 type)
{
	u32 reg, reg_idx, shift, val;

	/*
	 * Select the appropriate event select register(L3C_EVENT_TYPE0/1).
	 * There are 2 event select registers for the 8 hardware counters.
	 * Event code is 8-bits and for the former 4 hardware counters,
	 * L3C_EVENT_TYPE0 is chosen. For the latter 4 hardware counters,
	 * L3C_EVENT_TYPE1 is chosen.
	 */
	reg = L3C_EVENT_TYPE0 + (idx / 4) * 4;
	reg_idx = idx % 4;
	shift = 8 * reg_idx;

	/* Write event code to L3C_EVENT_TYPEx Register */
	val = readl(l3c_pmu->base + reg);
	val &= ~(L3C_EVTYPE_NONE << shift);
	val |= (type << shift);
	writel(val, l3c_pmu->base + reg);
}
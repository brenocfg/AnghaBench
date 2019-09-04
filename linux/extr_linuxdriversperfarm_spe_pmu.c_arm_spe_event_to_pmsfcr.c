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
struct perf_event_attr {int dummy; } ;
struct perf_event {struct perf_event_attr attr; } ;

/* Variables and functions */
 int ATTR_CFG_GET_FLD (struct perf_event_attr*,int /*<<< orphan*/ ) ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int SYS_PMSFCR_EL1_B_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSFCR_EL1_FE_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSFCR_EL1_FL_SHIFT ; 
 int /*<<< orphan*/  SYS_PMSFCR_EL1_FT_SHIFT ; 
 int SYS_PMSFCR_EL1_LD_SHIFT ; 
 int SYS_PMSFCR_EL1_ST_SHIFT ; 
 int /*<<< orphan*/  branch_filter ; 
 int /*<<< orphan*/  event_filter ; 
 int /*<<< orphan*/  load_filter ; 
 int /*<<< orphan*/  min_latency ; 
 int /*<<< orphan*/  store_filter ; 

__attribute__((used)) static u64 arm_spe_event_to_pmsfcr(struct perf_event *event)
{
	struct perf_event_attr *attr = &event->attr;
	u64 reg = 0;

	reg |= ATTR_CFG_GET_FLD(attr, load_filter) << SYS_PMSFCR_EL1_LD_SHIFT;
	reg |= ATTR_CFG_GET_FLD(attr, store_filter) << SYS_PMSFCR_EL1_ST_SHIFT;
	reg |= ATTR_CFG_GET_FLD(attr, branch_filter) << SYS_PMSFCR_EL1_B_SHIFT;

	if (reg)
		reg |= BIT(SYS_PMSFCR_EL1_FT_SHIFT);

	if (ATTR_CFG_GET_FLD(attr, event_filter))
		reg |= BIT(SYS_PMSFCR_EL1_FE_SHIFT);

	if (ATTR_CFG_GET_FLD(attr, min_latency))
		reg |= BIT(SYS_PMSFCR_EL1_FL_SHIFT);

	return reg;
}
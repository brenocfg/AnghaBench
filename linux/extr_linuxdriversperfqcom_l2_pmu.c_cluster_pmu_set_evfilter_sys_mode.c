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
 int /*<<< orphan*/  IA_L2PMXEVFILTER ; 
 int L2PMXEVFILTER_ORGFILTER_ALL ; 
 int L2PMXEVFILTER_ORGFILTER_IDINDEP ; 
 int L2PMXEVFILTER_SUFILTER_ALL ; 
 int /*<<< orphan*/  reg_idx (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_l2_indirect_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void cluster_pmu_set_evfilter_sys_mode(u32 ctr)
{
	u32 val =  L2PMXEVFILTER_SUFILTER_ALL |
		   L2PMXEVFILTER_ORGFILTER_IDINDEP |
		   L2PMXEVFILTER_ORGFILTER_ALL;

	set_l2_indirect_reg(reg_idx(IA_L2PMXEVFILTER, ctr), val);
}
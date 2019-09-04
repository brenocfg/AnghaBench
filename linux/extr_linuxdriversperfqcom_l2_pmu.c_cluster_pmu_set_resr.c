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
typedef  int u32 ;
struct cluster_pmu {int /*<<< orphan*/  pmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2PMRESR ; 
 int L2PMRESR_EN ; 
 int L2PMRESR_GROUP_BITS ; 
 int L2PMRESR_GROUP_MASK ; 
 int get_l2_indirect_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_l2_indirect_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cluster_pmu_set_resr(struct cluster_pmu *cluster,
			       u32 event_group, u32 event_cc)
{
	u64 field;
	u64 resr_val;
	u32 shift;
	unsigned long flags;

	shift = L2PMRESR_GROUP_BITS * event_group;
	field = ((u64)(event_cc & L2PMRESR_GROUP_MASK) << shift);

	spin_lock_irqsave(&cluster->pmu_lock, flags);

	resr_val = get_l2_indirect_reg(L2PMRESR);
	resr_val &= ~(L2PMRESR_GROUP_MASK << shift);
	resr_val |= field;
	resr_val |= L2PMRESR_EN;
	set_l2_indirect_reg(L2PMRESR, resr_val);

	spin_unlock_irqrestore(&cluster->pmu_lock, flags);
}
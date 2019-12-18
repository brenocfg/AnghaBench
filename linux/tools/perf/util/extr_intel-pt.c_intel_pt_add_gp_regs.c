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
struct regs_dump {int mask; } ;
struct intel_pt_blk_items {int** val; int* mask; } ;

/* Variables and functions */
 size_t INTEL_PT_GP_REGS_POS ; 
 int PERF_REG_X86_64_MAX ; 
 int* pebs_gp_regs ; 

__attribute__((used)) static u64 *intel_pt_add_gp_regs(struct regs_dump *intr_regs, u64 *pos,
				 const struct intel_pt_blk_items *items,
				 u64 regs_mask)
{
	const u64 *gp_regs = items->val[INTEL_PT_GP_REGS_POS];
	u32 mask = items->mask[INTEL_PT_GP_REGS_POS];
	u32 bit;
	int i;

	for (i = 0, bit = 1; i < PERF_REG_X86_64_MAX; i++, bit <<= 1) {
		/* Get the PEBS gp_regs array index */
		int n = pebs_gp_regs[i] - 1;

		if (n < 0)
			continue;
		/*
		 * Add only registers that were requested (i.e. 'regs_mask') and
		 * that were provided (i.e. 'mask'), and update the resulting
		 * mask (i.e. 'intr_regs->mask') accordingly.
		 */
		if (mask & 1 << n && regs_mask & bit) {
			intr_regs->mask |= bit;
			*pos++ = gp_regs[n];
		}
	}

	return pos;
}
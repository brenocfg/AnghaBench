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
struct intel_pt_blk_items {int has_xmm; int* xmm; } ;

/* Variables and functions */
 int PERF_REG_X86_XMM0 ; 

__attribute__((used)) static void intel_pt_add_xmm(struct regs_dump *intr_regs, u64 *pos,
			     const struct intel_pt_blk_items *items,
			     u64 regs_mask)
{
	u32 mask = items->has_xmm & (regs_mask >> PERF_REG_X86_XMM0);
	const u64 *xmm = items->xmm;

	/*
	 * If there are any XMM registers, then there should be all of them.
	 * Nevertheless, follow the logic to add only registers that were
	 * requested (i.e. 'regs_mask') and that were provided (i.e. 'mask'),
	 * and update the resulting mask (i.e. 'intr_regs->mask') accordingly.
	 */
	intr_regs->mask |= (u64)mask << PERF_REG_X86_XMM0;

	for (; mask; mask >>= 1, xmm++) {
		if (mask & 1)
			*pos++ = *xmm;
	}
}
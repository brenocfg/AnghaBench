#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct intel_pt_blk_items {int* mask; int /*<<< orphan*/ ** val; } ;
struct branch_stack {scalar_t__ nr; TYPE_1__* entries; } ;
struct TYPE_2__ {int /*<<< orphan*/  from; } ;

/* Variables and functions */
 int INTEL_PT_LBR_0_POS ; 
 int INTEL_PT_LBR_2_POS ; 
 int /*<<< orphan*/  intel_pt_lbr_flags (int /*<<< orphan*/  const) ; 

__attribute__((used)) static void intel_pt_add_lbrs(struct branch_stack *br_stack,
			      const struct intel_pt_blk_items *items)
{
	u64 *to;
	int i;

	br_stack->nr = 0;

	to = &br_stack->entries[0].from;

	for (i = INTEL_PT_LBR_0_POS; i <= INTEL_PT_LBR_2_POS; i++) {
		u32 mask = items->mask[i];
		const u64 *from = items->val[i];

		for (; mask; mask >>= 3, from += 3) {
			if ((mask & 7) == 7) {
				*to++ = from[0];
				*to++ = from[1];
				*to++ = intel_pt_lbr_flags(from[2]);
				br_stack->nr += 1;
			}
		}
	}
}
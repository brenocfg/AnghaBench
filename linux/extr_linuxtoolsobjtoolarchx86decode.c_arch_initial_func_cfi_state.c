#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int offset; int /*<<< orphan*/  base; } ;
struct cfi_state {TYPE_2__* regs; TYPE_1__ cfa; } ;
struct TYPE_4__ {int offset; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFI_CFA ; 
 int CFI_NUM_REGS ; 
 int /*<<< orphan*/  CFI_SP ; 
 int /*<<< orphan*/  CFI_UNDEFINED ; 

void arch_initial_func_cfi_state(struct cfi_state *state)
{
	int i;

	for (i = 0; i < CFI_NUM_REGS; i++) {
		state->regs[i].base = CFI_UNDEFINED;
		state->regs[i].offset = 0;
	}

	/* initial CFA (call frame address) */
	state->cfa.base = CFI_SP;
	state->cfa.offset = 8;

	/* initial RA (return address) */
	state->regs[16].base = CFI_CFA;
	state->regs[16].offset = -8;
}
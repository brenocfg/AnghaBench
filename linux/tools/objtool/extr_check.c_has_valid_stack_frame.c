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
struct TYPE_3__ {size_t base; } ;
struct insn_state {TYPE_2__* regs; scalar_t__ drap; TYPE_1__ cfa; } ;
struct TYPE_4__ {size_t base; int offset; } ;

/* Variables and functions */
 size_t CFI_BP ; 
 size_t CFI_CFA ; 

__attribute__((used)) static bool has_valid_stack_frame(struct insn_state *state)
{
	if (state->cfa.base == CFI_BP && state->regs[CFI_BP].base == CFI_CFA &&
	    state->regs[CFI_BP].offset == -16)
		return true;

	if (state->drap && state->regs[CFI_BP].base == CFI_BP)
		return true;

	return false;
}
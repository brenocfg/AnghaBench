#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* base; } ;
struct insn_state {int drap_offset; void* drap_reg; TYPE_3__* vals; TYPE_2__* regs; TYPE_1__ cfa; } ;
struct TYPE_6__ {void* base; } ;
struct TYPE_5__ {void* base; } ;

/* Variables and functions */
 int CFI_NUM_REGS ; 
 void* CFI_UNDEFINED ; 
 int /*<<< orphan*/  memset (struct insn_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_insn_state(struct insn_state *state)
{
	int i;

	memset(state, 0, sizeof(*state));
	state->cfa.base = CFI_UNDEFINED;
	for (i = 0; i < CFI_NUM_REGS; i++) {
		state->regs[i].base = CFI_UNDEFINED;
		state->vals[i].base = CFI_UNDEFINED;
	}
	state->drap_reg = CFI_UNDEFINED;
	state->drap_offset = -1;
}
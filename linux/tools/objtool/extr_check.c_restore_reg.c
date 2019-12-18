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
struct insn_state {TYPE_1__* regs; } ;
struct TYPE_2__ {scalar_t__ offset; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFI_UNDEFINED ; 

__attribute__((used)) static void restore_reg(struct insn_state *state, unsigned char reg)
{
	state->regs[reg].base = CFI_UNDEFINED;
	state->regs[reg].offset = 0;
}
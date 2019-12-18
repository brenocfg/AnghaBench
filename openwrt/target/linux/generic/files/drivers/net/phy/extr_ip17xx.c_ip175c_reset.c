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
struct ip17xx_state {TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  MODE_REG; int /*<<< orphan*/  MODE_VAL; } ;

/* Variables and functions */
 scalar_t__ REG_SUPP (int /*<<< orphan*/ ) ; 
 int getPhy (struct ip17xx_state*,int /*<<< orphan*/ ) ; 
 int ip175c_update_state (struct ip17xx_state*) ; 
 int setPhy (struct ip17xx_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ip175c_reset(struct ip17xx_state *state)
{
	int err;

	if (REG_SUPP(state->regs->MODE_REG)) {
		err = setPhy(state, state->regs->MODE_REG, state->regs->MODE_VAL);
		if (err < 0)
			return err;
		err = getPhy(state, state->regs->MODE_REG);
		if (err < 0)
			return err;
	}

	return ip175c_update_state(state);
}
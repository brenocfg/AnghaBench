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
struct ip17xx_state {int num_vlans; TYPE_1__* regs; scalar_t__ vlan_enabled; scalar_t__ router_mode; } ;
struct TYPE_2__ {int ROUTER_EN_BIT; int TAG_VLAN_BIT; int NUMLAN_GROUPS_BIT; int NUMLAN_GROUPS_MAX; int /*<<< orphan*/  ROUTER_CONTROL_REG; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SUPP (int /*<<< orphan*/ ) ; 
 int getPhy (struct ip17xx_state*,int /*<<< orphan*/ ) ; 
 int setPhy (struct ip17xx_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ip175c_set_flags(struct ip17xx_state *state)
{
	int val;

	if (!REG_SUPP(state->regs->ROUTER_CONTROL_REG)) {
		return 0;
	}

	val = getPhy(state, state->regs->ROUTER_CONTROL_REG);
	if (val < 0) {
		return val;
	}
	if (state->regs->ROUTER_EN_BIT >= 0) {
		if (state->router_mode) {
			val |= (1<<state->regs->ROUTER_EN_BIT);
		} else {
			val &= (~(1<<state->regs->ROUTER_EN_BIT));
		}
	}
	if (state->regs->TAG_VLAN_BIT >= 0) {
		if (state->vlan_enabled) {
			val |= (1<<state->regs->TAG_VLAN_BIT);
		} else {
			val &= (~(1<<state->regs->TAG_VLAN_BIT));
		}
	}
	if (state->regs->NUMLAN_GROUPS_BIT >= 0) {
		val &= (~((state->regs->NUMLAN_GROUPS_MAX-1)<<state->regs->NUMLAN_GROUPS_BIT));
		if (state->num_vlans > state->regs->NUMLAN_GROUPS_MAX) {
			val |= state->regs->NUMLAN_GROUPS_MAX << state->regs->NUMLAN_GROUPS_BIT;
		} else if (state->num_vlans >= 1) {
			val |= (state->num_vlans-1) << state->regs->NUMLAN_GROUPS_BIT;
		}
	}
	return setPhy(state, state->regs->ROUTER_CONTROL_REG, val);
}
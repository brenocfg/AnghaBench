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
struct switch_dev {int dummy; } ;
struct ip17xx_state {TYPE_2__* regs; TYPE_1__* ports; } ;
struct TYPE_4__ {int (* update_state ) (struct ip17xx_state*) ;} ;
struct TYPE_3__ {int pvid; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_VLANS ; 
 struct ip17xx_state* get_state (struct switch_dev*) ; 
 int stub1 (struct ip17xx_state*) ; 

__attribute__((used)) static int ip17xx_set_pvid(struct switch_dev *dev, int port, int val)
{
	struct ip17xx_state *state = get_state(dev);

	if (val < 0 || val >= MAX_VLANS)
		return -EINVAL;

	state->ports[port].pvid = val;
	return state->regs->update_state(state);
}
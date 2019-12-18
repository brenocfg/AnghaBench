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
struct TYPE_4__ {int i; } ;
struct switch_val {int port_vlan; TYPE_2__ value; } ;
struct switch_dev {int ports; } ;
struct switch_attr {int dummy; } ;
struct ip17xx_state {TYPE_1__* regs; } ;
struct TYPE_3__ {int CPU_PORT; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 struct ip17xx_state* get_state (struct switch_dev*) ; 
 int ip_phy_read (struct ip17xx_state*,int,int) ; 

__attribute__((used)) static int ip17xx_get_port_speed(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
	struct ip17xx_state *state = get_state(dev);
	int nr = val->port_vlan;
	int speed, status;

	if (nr == state->regs->CPU_PORT) {
		val->value.i = 100;
		return 0;
	}

	if (nr >= dev->ports || nr < 0)
		return -EINVAL;

	status = ip_phy_read(state, nr, 1);
	speed = ip_phy_read(state, nr, 18);
	if (status < 0 || speed < 0)
		return -EIO;

	if (status & 4)
		val->value.i = ((speed & (1<<11)) ? 100 : 10);
	else
		val->value.i = 0;

	return 0;
}
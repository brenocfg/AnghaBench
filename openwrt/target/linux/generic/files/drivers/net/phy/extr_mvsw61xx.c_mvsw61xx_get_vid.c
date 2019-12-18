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
struct TYPE_3__ {int /*<<< orphan*/  i; } ;
struct switch_val {int port_vlan; TYPE_1__ value; } ;
struct switch_dev {int vlans; } ;
struct switch_attr {int dummy; } ;
struct mvsw61xx_state {TYPE_2__* vlans; } ;
struct TYPE_4__ {int /*<<< orphan*/  vid; } ;

/* Variables and functions */
 int EINVAL ; 
 struct mvsw61xx_state* get_state (struct switch_dev*) ; 

__attribute__((used)) static int mvsw61xx_get_vid(struct switch_dev *dev,
		const struct switch_attr *attr, struct switch_val *val)
{
	struct mvsw61xx_state *state = get_state(dev);
	int vno = val->port_vlan;

	if (vno <= 0 || vno >= dev->vlans)
		return -EINVAL;

	val->value.i = state->vlans[vno].vid;

	return 0;
}
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
struct switch_val {TYPE_1__ value; } ;
struct switch_dev {int dummy; } ;
struct switch_attr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  m; } ;
struct ip17xx_state {TYPE_2__ proc_mii; } ;

/* Variables and functions */
 struct ip17xx_state* get_state (struct switch_dev*) ; 

__attribute__((used)) static int ip17xx_get_reg(struct switch_dev *dev, const struct switch_attr *attr, struct switch_val *val)
{
	struct ip17xx_state *state = get_state(dev);

	val->value.i = state->proc_mii.m;
	return 0;
}
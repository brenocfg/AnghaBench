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
struct device {struct dev_pin_info* pins; } ;
struct dev_pin_info {scalar_t__ init_state; scalar_t__ default_state; TYPE_1__* p; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int pinctrl_select_state (TYPE_1__*,scalar_t__) ; 

int pinctrl_init_done(struct device *dev)
{
	struct dev_pin_info *pins = dev->pins;
	int ret;

	if (!pins)
		return 0;

	if (IS_ERR(pins->init_state))
		return 0; /* No such state */

	if (pins->p->state != pins->init_state)
		return 0; /* Not at init anyway */

	if (IS_ERR(pins->default_state))
		return 0; /* No default state */

	ret = pinctrl_select_state(pins->p, pins->default_state);
	if (ret)
		dev_err(dev, "failed to activate default pinctrl state\n");

	return ret;
}
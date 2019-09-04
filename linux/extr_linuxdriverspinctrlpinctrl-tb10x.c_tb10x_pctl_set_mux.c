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
struct tb10x_pinfuncgrp {size_t port; scalar_t__ mode; int pincnt; int /*<<< orphan*/ * pins; } ;
struct tb10x_pinctrl {int /*<<< orphan*/  mutex; TYPE_1__* ports; int /*<<< orphan*/  gpios; struct tb10x_pinfuncgrp* pingroups; } ;
struct pinctrl_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ mode; scalar_t__ count; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tb10x_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 
 int /*<<< orphan*/  tb10x_pinctrl_set_config (struct tb10x_pinctrl*,size_t,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tb10x_pctl_set_mux(struct pinctrl_dev *pctl,
			unsigned func_selector, unsigned group_selector)
{
	struct tb10x_pinctrl *state = pinctrl_dev_get_drvdata(pctl);
	const struct tb10x_pinfuncgrp *grp = &state->pingroups[group_selector];
	int i;

	if (grp->port < 0)
		return 0;

	mutex_lock(&state->mutex);

	/*
	 * Check if the requested function is compatible with previously
	 * requested functions.
	 */
	if (state->ports[grp->port].count
			&& (state->ports[grp->port].mode != grp->mode)) {
		mutex_unlock(&state->mutex);
		return -EBUSY;
	}

	/*
	 * Check if the requested function is compatible with previously
	 * requested GPIOs.
	 */
	for (i = 0; i < grp->pincnt; i++)
		if (test_bit(grp->pins[i], state->gpios)) {
			mutex_unlock(&state->mutex);
			return -EBUSY;
		}

	tb10x_pinctrl_set_config(state, grp->port, grp->mode);

	state->ports[grp->port].count++;

	mutex_unlock(&state->mutex);

	return 0;
}
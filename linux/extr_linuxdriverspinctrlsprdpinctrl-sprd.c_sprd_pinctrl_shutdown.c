#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pinctrl_state {int dummy; } ;
typedef  struct pinctrl_state pinctrl ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct pinctrl_state*) ; 
 struct pinctrl_state* devm_pinctrl_get (int /*<<< orphan*/ *) ; 
 struct pinctrl_state* pinctrl_lookup_state (struct pinctrl_state*,char*) ; 
 int /*<<< orphan*/  pinctrl_select_state (struct pinctrl_state*,struct pinctrl_state*) ; 

void sprd_pinctrl_shutdown(struct platform_device *pdev)
{
	struct pinctrl *pinctl;
	struct pinctrl_state *state;

	pinctl = devm_pinctrl_get(&pdev->dev);
	if (IS_ERR(pinctl))
		return;
	state = pinctrl_lookup_state(pinctl, "shutdown");
	if (IS_ERR(state))
		return;
	pinctrl_select_state(pinctl, state);
}
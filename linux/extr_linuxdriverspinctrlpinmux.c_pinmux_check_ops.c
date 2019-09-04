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
struct pinmux_ops {unsigned int (* get_functions_count ) (struct pinctrl_dev*) ;char* (* get_function_name ) (struct pinctrl_dev*,unsigned int) ;int /*<<< orphan*/  set_mux; int /*<<< orphan*/  get_function_groups; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; TYPE_1__* desc; } ;
struct TYPE_2__ {struct pinmux_ops* pmxops; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int stub1 (struct pinctrl_dev*) ; 
 char* stub2 (struct pinctrl_dev*,unsigned int) ; 

int pinmux_check_ops(struct pinctrl_dev *pctldev)
{
	const struct pinmux_ops *ops = pctldev->desc->pmxops;
	unsigned nfuncs;
	unsigned selector = 0;

	/* Check that we implement required operations */
	if (!ops ||
	    !ops->get_functions_count ||
	    !ops->get_function_name ||
	    !ops->get_function_groups ||
	    !ops->set_mux) {
		dev_err(pctldev->dev, "pinmux ops lacks necessary functions\n");
		return -EINVAL;
	}
	/* Check that all functions registered have names */
	nfuncs = ops->get_functions_count(pctldev);
	while (selector < nfuncs) {
		const char *fname = ops->get_function_name(pctldev,
							   selector);
		if (!fname) {
			dev_err(pctldev->dev, "pinmux ops has no name for function%u\n",
				selector);
			return -EINVAL;
		}
		selector++;
	}

	return 0;
}
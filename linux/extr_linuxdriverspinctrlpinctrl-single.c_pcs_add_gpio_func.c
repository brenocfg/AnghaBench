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
struct pcs_gpiofunc_range {int /*<<< orphan*/  node; int /*<<< orphan*/  gpiofunc; int /*<<< orphan*/  npins; int /*<<< orphan*/  offset; } ;
struct pcs_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  gpiofuncs; int /*<<< orphan*/  dev; } ;
struct of_phandle_args {int /*<<< orphan*/ * args; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct pcs_gpiofunc_range* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int of_parse_phandle_with_args (struct device_node*,char const*,char const*,int,struct of_phandle_args*) ; 

__attribute__((used)) static int pcs_add_gpio_func(struct device_node *node, struct pcs_device *pcs)
{
	const char *propname = "pinctrl-single,gpio-range";
	const char *cellname = "#pinctrl-single,gpio-range-cells";
	struct of_phandle_args gpiospec;
	struct pcs_gpiofunc_range *range;
	int ret, i;

	for (i = 0; ; i++) {
		ret = of_parse_phandle_with_args(node, propname, cellname,
						 i, &gpiospec);
		/* Do not treat it as error. Only treat it as end condition. */
		if (ret) {
			ret = 0;
			break;
		}
		range = devm_kzalloc(pcs->dev, sizeof(*range), GFP_KERNEL);
		if (!range) {
			ret = -ENOMEM;
			break;
		}
		range->offset = gpiospec.args[0];
		range->npins = gpiospec.args[1];
		range->gpiofunc = gpiospec.args[2];
		mutex_lock(&pcs->mutex);
		list_add_tail(&range->node, &pcs->gpiofuncs);
		mutex_unlock(&pcs->mutex);
	}
	return ret;
}
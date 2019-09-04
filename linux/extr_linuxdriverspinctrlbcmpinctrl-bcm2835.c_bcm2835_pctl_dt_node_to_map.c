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
typedef  int u32 ;
struct property {int length; } ;
struct pinctrl_map {int dummy; } ;
struct pinctrl_dev {int dummy; } ;
struct device_node {int dummy; } ;
struct bcm2835_pinctrl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bcm2835_gpio_pins ; 
 int /*<<< orphan*/  bcm2835_pctl_dt_free_map (struct pinctrl_dev*,struct pinctrl_map*,int) ; 
 int bcm2835_pctl_dt_node_to_map_func (struct bcm2835_pinctrl*,struct device_node*,int,int,struct pinctrl_map**) ; 
 int bcm2835_pctl_dt_node_to_map_pull (struct bcm2835_pinctrl*,struct device_node*,int,int,struct pinctrl_map**) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct device_node*,...) ; 
 struct pinctrl_map* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int*) ; 
 int pinconf_generic_dt_node_to_map_all (struct pinctrl_dev*,struct device_node*,struct pinctrl_map**,unsigned int*) ; 
 struct bcm2835_pinctrl* pinctrl_dev_get_drvdata (struct pinctrl_dev*) ; 

__attribute__((used)) static int bcm2835_pctl_dt_node_to_map(struct pinctrl_dev *pctldev,
		struct device_node *np,
		struct pinctrl_map **map, unsigned int *num_maps)
{
	struct bcm2835_pinctrl *pc = pinctrl_dev_get_drvdata(pctldev);
	struct property *pins, *funcs, *pulls;
	int num_pins, num_funcs, num_pulls, maps_per_pin;
	struct pinctrl_map *maps, *cur_map;
	int i, err;
	u32 pin, func, pull;

	/* Check for generic binding in this node */
	err = pinconf_generic_dt_node_to_map_all(pctldev, np, map, num_maps);
	if (err || *num_maps)
		return err;

	/* Generic binding did not find anything continue with legacy parse */
	pins = of_find_property(np, "brcm,pins", NULL);
	if (!pins) {
		dev_err(pc->dev, "%pOF: missing brcm,pins property\n", np);
		return -EINVAL;
	}

	funcs = of_find_property(np, "brcm,function", NULL);
	pulls = of_find_property(np, "brcm,pull", NULL);

	if (!funcs && !pulls) {
		dev_err(pc->dev,
			"%pOF: neither brcm,function nor brcm,pull specified\n",
			np);
		return -EINVAL;
	}

	num_pins = pins->length / 4;
	num_funcs = funcs ? (funcs->length / 4) : 0;
	num_pulls = pulls ? (pulls->length / 4) : 0;

	if (num_funcs > 1 && num_funcs != num_pins) {
		dev_err(pc->dev,
			"%pOF: brcm,function must have 1 or %d entries\n",
			np, num_pins);
		return -EINVAL;
	}

	if (num_pulls > 1 && num_pulls != num_pins) {
		dev_err(pc->dev,
			"%pOF: brcm,pull must have 1 or %d entries\n",
			np, num_pins);
		return -EINVAL;
	}

	maps_per_pin = 0;
	if (num_funcs)
		maps_per_pin++;
	if (num_pulls)
		maps_per_pin++;
	cur_map = maps = kcalloc(num_pins * maps_per_pin, sizeof(*maps),
				 GFP_KERNEL);
	if (!maps)
		return -ENOMEM;

	for (i = 0; i < num_pins; i++) {
		err = of_property_read_u32_index(np, "brcm,pins", i, &pin);
		if (err)
			goto out;
		if (pin >= ARRAY_SIZE(bcm2835_gpio_pins)) {
			dev_err(pc->dev, "%pOF: invalid brcm,pins value %d\n",
				np, pin);
			err = -EINVAL;
			goto out;
		}

		if (num_funcs) {
			err = of_property_read_u32_index(np, "brcm,function",
					(num_funcs > 1) ? i : 0, &func);
			if (err)
				goto out;
			err = bcm2835_pctl_dt_node_to_map_func(pc, np, pin,
							func, &cur_map);
			if (err)
				goto out;
		}
		if (num_pulls) {
			err = of_property_read_u32_index(np, "brcm,pull",
					(num_pulls > 1) ? i : 0, &pull);
			if (err)
				goto out;
			err = bcm2835_pctl_dt_node_to_map_pull(pc, np, pin,
							pull, &cur_map);
			if (err)
				goto out;
		}
	}

	*map = maps;
	*num_maps = num_pins * maps_per_pin;

	return 0;

out:
	bcm2835_pctl_dt_free_map(pctldev, maps, num_pins * maps_per_pin);
	return err;
}
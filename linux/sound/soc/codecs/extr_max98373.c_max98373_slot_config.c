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
struct max98373_priv {int v_slot; int i_slot; int reset_gpio; int spkfb_slot; } ;
struct device {TYPE_1__* of_node; } ;
struct i2c_client {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  full_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_property_read_u32 (struct device*,char*,int*) ; 
 int /*<<< orphan*/  gpio_is_valid (int) ; 
 int of_get_named_gpio (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void max98373_slot_config(struct i2c_client *i2c,
	struct max98373_priv *max98373)
{
	int value;
	struct device *dev = &i2c->dev;

	if (!device_property_read_u32(dev, "maxim,vmon-slot-no", &value))
		max98373->v_slot = value & 0xF;
	else
		max98373->v_slot = 0;

	if (!device_property_read_u32(dev, "maxim,imon-slot-no", &value))
		max98373->i_slot = value & 0xF;
	else
		max98373->i_slot = 1;
	if (dev->of_node) {
		max98373->reset_gpio = of_get_named_gpio(dev->of_node,
						"maxim,reset-gpio", 0);
		if (!gpio_is_valid(max98373->reset_gpio)) {
			dev_err(dev, "Looking up %s property in node %s failed %d\n",
				"maxim,reset-gpio", dev->of_node->full_name,
				max98373->reset_gpio);
		} else {
			dev_dbg(dev, "maxim,reset-gpio=%d",
				max98373->reset_gpio);
		}
	} else {
		/* this makes reset_gpio as invalid */
		max98373->reset_gpio = -1;
	}

	if (!device_property_read_u32(dev, "maxim,spkfb-slot-no", &value))
		max98373->spkfb_slot = value & 0xF;
	else
		max98373->spkfb_slot = 2;
}
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
typedef  scalar_t__ u32 ;
struct usb_phy_generic_platform_data {int type; int needs_vcc; void* gpiod_vbus; int /*<<< orphan*/  gpio_reset; scalar_t__ clk_rate; } ;
struct TYPE_3__ {char* label; int type; TYPE_2__* otg; int /*<<< orphan*/  set_suspend; struct device* dev; } ;
struct usb_phy_generic {TYPE_1__ phy; struct device* dev; int /*<<< orphan*/  vcc; int /*<<< orphan*/  clk; void* gpiod_reset; void* gpiod_vbus; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
typedef  enum usb_phy_type { ____Placeholder_usb_phy_type } usb_phy_type ;
struct TYPE_4__ {int /*<<< orphan*/  set_peripheral; int /*<<< orphan*/  set_host; TYPE_1__* usb_phy; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_ASIS ; 
 int /*<<< orphan*/  GPIOF_ACTIVE_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OTG_STATE_UNDEFINED ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 int USB_PHY_TYPE_USB2 ; 
 int clk_set_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int devm_gpio_request_one (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 void* gpio_to_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_direction_output (void*,int) ; 
 int /*<<< orphan*/  nop_set_host ; 
 int /*<<< orphan*/  nop_set_peripheral ; 
 int /*<<< orphan*/  nop_set_suspend ; 
 int of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

int usb_phy_gen_create_phy(struct device *dev, struct usb_phy_generic *nop,
		struct usb_phy_generic_platform_data *pdata)
{
	enum usb_phy_type type = USB_PHY_TYPE_USB2;
	int err = 0;

	u32 clk_rate = 0;
	bool needs_vcc = false, needs_clk = false;

	if (dev->of_node) {
		struct device_node *node = dev->of_node;

		if (of_property_read_u32(node, "clock-frequency", &clk_rate))
			clk_rate = 0;

		needs_vcc = of_property_read_bool(node, "vcc-supply");
		needs_clk = of_property_read_bool(node, "clocks");
		nop->gpiod_reset = devm_gpiod_get_optional(dev, "reset",
							   GPIOD_ASIS);
		err = PTR_ERR_OR_ZERO(nop->gpiod_reset);
		if (!err) {
			nop->gpiod_vbus = devm_gpiod_get_optional(dev,
							 "vbus-detect",
							 GPIOD_ASIS);
			err = PTR_ERR_OR_ZERO(nop->gpiod_vbus);
		}
	} else if (pdata) {
		type = pdata->type;
		clk_rate = pdata->clk_rate;
		needs_vcc = pdata->needs_vcc;
		if (gpio_is_valid(pdata->gpio_reset)) {
			err = devm_gpio_request_one(dev, pdata->gpio_reset,
						    GPIOF_ACTIVE_LOW,
						    dev_name(dev));
			if (!err)
				nop->gpiod_reset =
					gpio_to_desc(pdata->gpio_reset);
		}
		nop->gpiod_vbus = pdata->gpiod_vbus;
	}

	if (err == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	if (err) {
		dev_err(dev, "Error requesting RESET or VBUS GPIO\n");
		return err;
	}
	if (nop->gpiod_reset)
		gpiod_direction_output(nop->gpiod_reset, 1);

	nop->phy.otg = devm_kzalloc(dev, sizeof(*nop->phy.otg),
			GFP_KERNEL);
	if (!nop->phy.otg)
		return -ENOMEM;

	nop->clk = devm_clk_get(dev, "main_clk");
	if (IS_ERR(nop->clk)) {
		dev_dbg(dev, "Can't get phy clock: %ld\n",
					PTR_ERR(nop->clk));
		if (needs_clk)
			return PTR_ERR(nop->clk);
	}

	if (!IS_ERR(nop->clk) && clk_rate) {
		err = clk_set_rate(nop->clk, clk_rate);
		if (err) {
			dev_err(dev, "Error setting clock rate\n");
			return err;
		}
	}

	nop->vcc = devm_regulator_get(dev, "vcc");
	if (IS_ERR(nop->vcc)) {
		dev_dbg(dev, "Error getting vcc regulator: %ld\n",
					PTR_ERR(nop->vcc));
		if (needs_vcc)
			return -EPROBE_DEFER;
	}

	nop->dev		= dev;
	nop->phy.dev		= nop->dev;
	nop->phy.label		= "nop-xceiv";
	nop->phy.set_suspend	= nop_set_suspend;
	nop->phy.type		= type;

	nop->phy.otg->state		= OTG_STATE_UNDEFINED;
	nop->phy.otg->usb_phy		= &nop->phy;
	nop->phy.otg->set_host		= nop_set_host;
	nop->phy.otg->set_peripheral	= nop_set_peripheral;

	return 0;
}
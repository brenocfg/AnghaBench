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
struct cpcap_phy_ddata {int /*<<< orphan*/ * pins_uart; int /*<<< orphan*/ * pins; int /*<<< orphan*/  dev; int /*<<< orphan*/ * pins_utmi; int /*<<< orphan*/ * pins_ulpi; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * devm_pinctrl_get (int /*<<< orphan*/ ) ; 
 void* pinctrl_lookup_state (int /*<<< orphan*/ *,char*) ; 
 int pinctrl_select_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cpcap_usb_init_optional_pins(struct cpcap_phy_ddata *ddata)
{
	ddata->pins = devm_pinctrl_get(ddata->dev);
	if (IS_ERR(ddata->pins)) {
		dev_info(ddata->dev, "default pins not configured: %ld\n",
			 PTR_ERR(ddata->pins));
		ddata->pins = NULL;

		return 0;
	}

	ddata->pins_ulpi = pinctrl_lookup_state(ddata->pins, "ulpi");
	if (IS_ERR(ddata->pins_ulpi)) {
		dev_info(ddata->dev, "ulpi pins not configured\n");
		ddata->pins_ulpi = NULL;
	}

	ddata->pins_utmi = pinctrl_lookup_state(ddata->pins, "utmi");
	if (IS_ERR(ddata->pins_utmi)) {
		dev_info(ddata->dev, "utmi pins not configured\n");
		ddata->pins_utmi = NULL;
	}

	ddata->pins_uart = pinctrl_lookup_state(ddata->pins, "uart");
	if (IS_ERR(ddata->pins_uart)) {
		dev_info(ddata->dev, "uart pins not configured\n");
		ddata->pins_uart = NULL;
	}

	if (ddata->pins_uart)
		return pinctrl_select_state(ddata->pins, ddata->pins_uart);

	return 0;
}
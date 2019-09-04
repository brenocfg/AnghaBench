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
struct max8903_pdata {int /*<<< orphan*/  cen; int /*<<< orphan*/  dcm; int /*<<< orphan*/  dok; } ;
struct TYPE_2__ {int type; } ;
struct max8903_data {int ta_in; int /*<<< orphan*/  psy; TYPE_1__ psy_desc; scalar_t__ usb_in; int /*<<< orphan*/  dev; struct max8903_pdata* pdata; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
typedef  enum power_supply_type { ____Placeholder_power_supply_type } power_supply_type ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int POWER_SUPPLY_TYPE_BATTERY ; 
 int POWER_SUPPLY_TYPE_MAINS ; 
 int POWER_SUPPLY_TYPE_USB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t max8903_dcin(int irq, void *_data)
{
	struct max8903_data *data = _data;
	struct max8903_pdata *pdata = data->pdata;
	bool ta_in;
	enum power_supply_type old_type;

	ta_in = gpio_get_value(pdata->dok) ? false : true;

	if (ta_in == data->ta_in)
		return IRQ_HANDLED;

	data->ta_in = ta_in;

	/* Set Current-Limit-Mode 1:DC 0:USB */
	if (gpio_is_valid(pdata->dcm))
		gpio_set_value(pdata->dcm, ta_in ? 1 : 0);

	/* Charger Enable / Disable (cen is negated) */
	if (gpio_is_valid(pdata->cen))
		gpio_set_value(pdata->cen, ta_in ? 0 :
				(data->usb_in ? 0 : 1));

	dev_dbg(data->dev, "TA(DC-IN) Charger %s.\n", ta_in ?
			"Connected" : "Disconnected");

	old_type = data->psy_desc.type;

	if (data->ta_in)
		data->psy_desc.type = POWER_SUPPLY_TYPE_MAINS;
	else if (data->usb_in)
		data->psy_desc.type = POWER_SUPPLY_TYPE_USB;
	else
		data->psy_desc.type = POWER_SUPPLY_TYPE_BATTERY;

	if (old_type != data->psy_desc.type)
		power_supply_changed(data->psy);

	return IRQ_HANDLED;
}
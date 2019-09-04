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
struct power_supply_desc {void* num_usb_types; void* usb_types; void* num_properties; void* properties; int /*<<< orphan*/  external_power_changed; int /*<<< orphan*/  get_property; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct power_supply_config {struct port_data* drv_data; } ;
struct power_supply {int dummy; } ;
struct port_data {int port_number; struct power_supply* psy; int /*<<< orphan*/  name; struct power_supply_desc psy_desc; struct charger_data* charger; } ;
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct cros_ec_device {int /*<<< orphan*/  event_notifier; scalar_t__ mkbp_event_supported; } ;
struct cros_ec_dev {struct cros_ec_device* ec_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct charger_data {int num_charger_ports; TYPE_1__ notifier; int /*<<< orphan*/  num_registered_psy; struct port_data** ports; struct cros_ec_device* ec_device; struct cros_ec_dev* ec_dev; struct device* dev; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 char* CHARGER_DIR_NAME ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct power_supply*) ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_USB ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int) ; 
 int blocking_notifier_chain_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cros_usbpd_charger_ec_event ; 
 int cros_usbpd_charger_get_num_ports (struct charger_data*) ; 
 int /*<<< orphan*/  cros_usbpd_charger_get_prop ; 
 int /*<<< orphan*/  cros_usbpd_charger_power_changed ; 
 void* cros_usbpd_charger_props ; 
 int /*<<< orphan*/  cros_usbpd_charger_unregister_notifier ; 
 void* cros_usbpd_charger_usb_types ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct cros_ec_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct charger_data*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct power_supply* devm_power_supply_register_no_ws (struct device*,struct power_supply_desc*,struct power_supply_config*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct charger_data*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int cros_usbpd_charger_probe(struct platform_device *pd)
{
	struct cros_ec_dev *ec_dev = dev_get_drvdata(pd->dev.parent);
	struct cros_ec_device *ec_device = ec_dev->ec_dev;
	struct power_supply_desc *psy_desc;
	struct device *dev = &pd->dev;
	struct charger_data *charger;
	struct power_supply *psy;
	struct port_data *port;
	int ret = -EINVAL;
	int i;

	charger = devm_kzalloc(dev, sizeof(struct charger_data),
			       GFP_KERNEL);
	if (!charger)
		return -ENOMEM;

	charger->dev = dev;
	charger->ec_dev = ec_dev;
	charger->ec_device = ec_device;

	platform_set_drvdata(pd, charger);

	charger->num_charger_ports = cros_usbpd_charger_get_num_ports(charger);
	if (charger->num_charger_ports <= 0) {
		/*
		 * This can happen on a system that doesn't support USB PD.
		 * Log a message, but no need to warn.
		 */
		dev_info(dev, "No charging ports found\n");
		ret = -ENODEV;
		goto fail_nowarn;
	}

	for (i = 0; i < charger->num_charger_ports; i++) {
		struct power_supply_config psy_cfg = {};

		port = devm_kzalloc(dev, sizeof(struct port_data), GFP_KERNEL);
		if (!port) {
			ret = -ENOMEM;
			goto fail;
		}

		port->charger = charger;
		port->port_number = i;
		sprintf(port->name, CHARGER_DIR_NAME, i);

		psy_desc = &port->psy_desc;
		psy_desc->name = port->name;
		psy_desc->type = POWER_SUPPLY_TYPE_USB;
		psy_desc->get_property = cros_usbpd_charger_get_prop;
		psy_desc->external_power_changed =
					cros_usbpd_charger_power_changed;
		psy_desc->properties = cros_usbpd_charger_props;
		psy_desc->num_properties =
					ARRAY_SIZE(cros_usbpd_charger_props);
		psy_desc->usb_types = cros_usbpd_charger_usb_types;
		psy_desc->num_usb_types =
				ARRAY_SIZE(cros_usbpd_charger_usb_types);
		psy_cfg.drv_data = port;

		psy = devm_power_supply_register_no_ws(dev, psy_desc,
						       &psy_cfg);
		if (IS_ERR(psy)) {
			dev_err(dev, "Failed to register power supply\n");
			continue;
		}
		port->psy = psy;

		charger->ports[charger->num_registered_psy++] = port;
	}

	if (!charger->num_registered_psy) {
		ret = -ENODEV;
		dev_err(dev, "No power supplies registered\n");
		goto fail;
	}

	if (ec_device->mkbp_event_supported) {
		/* Get PD events from the EC */
		charger->notifier.notifier_call = cros_usbpd_charger_ec_event;
		ret = blocking_notifier_chain_register(
						&ec_device->event_notifier,
						&charger->notifier);
		if (ret < 0) {
			dev_warn(dev, "failed to register notifier\n");
		} else {
			ret = devm_add_action_or_reset(dev,
					cros_usbpd_charger_unregister_notifier,
					charger);
			if (ret < 0)
				goto fail;
		}
	}

	return 0;

fail:
	WARN(1, "%s: Failing probe (err:0x%x)\n", dev_name(dev), ret);

fail_nowarn:
	dev_info(dev, "Failing probe (err:0x%x)\n", ret);
	return ret;
}
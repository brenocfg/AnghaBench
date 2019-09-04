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
struct TYPE_2__ {char* name; int /*<<< orphan*/  property_is_writeable; int /*<<< orphan*/  set_property; int /*<<< orphan*/  get_property; void* num_properties; void* properties; void* num_usb_types; void* usb_types; int /*<<< orphan*/  type; } ;
struct tcpm_port {int /*<<< orphan*/  psy; TYPE_1__ psy_desc; int /*<<< orphan*/  dev; int /*<<< orphan*/  usb_type; } ;
struct power_supply_config {int /*<<< orphan*/  fwnode; struct tcpm_port* drv_data; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_USB ; 
 int /*<<< orphan*/  POWER_SUPPLY_USB_TYPE_C ; 
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_fwnode (int /*<<< orphan*/ ) ; 
 char* dev_name (int /*<<< orphan*/ ) ; 
 char* devm_kzalloc (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (int /*<<< orphan*/ ,TYPE_1__*,struct power_supply_config*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char const*) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  tcpm_psy_get_prop ; 
 char* tcpm_psy_name_prefix ; 
 int /*<<< orphan*/  tcpm_psy_prop_writeable ; 
 void* tcpm_psy_props ; 
 int /*<<< orphan*/  tcpm_psy_set_prop ; 
 void* tcpm_psy_usb_types ; 

__attribute__((used)) static int devm_tcpm_psy_register(struct tcpm_port *port)
{
	struct power_supply_config psy_cfg = {};
	const char *port_dev_name = dev_name(port->dev);
	size_t psy_name_len = strlen(tcpm_psy_name_prefix) +
				     strlen(port_dev_name) + 1;
	char *psy_name;

	psy_cfg.drv_data = port;
	psy_cfg.fwnode = dev_fwnode(port->dev);
	psy_name = devm_kzalloc(port->dev, psy_name_len, GFP_KERNEL);
	if (!psy_name)
		return -ENOMEM;

	snprintf(psy_name, psy_name_len, "%s%s", tcpm_psy_name_prefix,
		 port_dev_name);
	port->psy_desc.name = psy_name;
	port->psy_desc.type = POWER_SUPPLY_TYPE_USB,
	port->psy_desc.usb_types = tcpm_psy_usb_types;
	port->psy_desc.num_usb_types = ARRAY_SIZE(tcpm_psy_usb_types);
	port->psy_desc.properties = tcpm_psy_props,
	port->psy_desc.num_properties = ARRAY_SIZE(tcpm_psy_props),
	port->psy_desc.get_property = tcpm_psy_get_prop,
	port->psy_desc.set_property = tcpm_psy_set_prop,
	port->psy_desc.property_is_writeable = tcpm_psy_prop_writeable,

	port->usb_type = POWER_SUPPLY_USB_TYPE_C;

	port->psy = devm_power_supply_register(port->dev, &port->psy_desc,
					       &psy_cfg);

	return PTR_ERR_OR_ZERO(port->psy);
}
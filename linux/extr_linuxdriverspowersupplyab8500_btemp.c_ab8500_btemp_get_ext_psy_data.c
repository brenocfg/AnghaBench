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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {TYPE_1__* desc; int /*<<< orphan*/  num_supplicants; scalar_t__ supplied_to; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int ac_conn; int usb_conn; } ;
struct ab8500_btemp {TYPE_2__ events; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_3__ {int num_properties; int* properties; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  POWER_SUPPLY_PROP_PRESENT 130 
#define  POWER_SUPPLY_TYPE_MAINS 129 
#define  POWER_SUPPLY_TYPE_USB 128 
 int /*<<< orphan*/  ab8500_btemp_periodic (struct ab8500_btemp*,int) ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 int match_string (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ab8500_btemp* power_supply_get_drvdata (struct power_supply*) ; 
 scalar_t__ power_supply_get_property (struct power_supply*,int,union power_supply_propval*) ; 

__attribute__((used)) static int ab8500_btemp_get_ext_psy_data(struct device *dev, void *data)
{
	struct power_supply *psy;
	struct power_supply *ext = dev_get_drvdata(dev);
	const char **supplicants = (const char **)ext->supplied_to;
	struct ab8500_btemp *di;
	union power_supply_propval ret;
	int j;

	psy = (struct power_supply *)data;
	di = power_supply_get_drvdata(psy);

	/*
	 * For all psy where the name of your driver
	 * appears in any supplied_to
	 */
	j = match_string(supplicants, ext->num_supplicants, psy->desc->name);
	if (j < 0)
		return 0;

	/* Go through all properties for the psy */
	for (j = 0; j < ext->desc->num_properties; j++) {
		enum power_supply_property prop;
		prop = ext->desc->properties[j];

		if (power_supply_get_property(ext, prop, &ret))
			continue;

		switch (prop) {
		case POWER_SUPPLY_PROP_PRESENT:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_MAINS:
				/* AC disconnected */
				if (!ret.intval && di->events.ac_conn) {
					di->events.ac_conn = false;
				}
				/* AC connected */
				else if (ret.intval && !di->events.ac_conn) {
					di->events.ac_conn = true;
					if (!di->events.usb_conn)
						ab8500_btemp_periodic(di, true);
				}
				break;
			case POWER_SUPPLY_TYPE_USB:
				/* USB disconnected */
				if (!ret.intval && di->events.usb_conn) {
					di->events.usb_conn = false;
				}
				/* USB connected */
				else if (ret.intval && !di->events.usb_conn) {
					di->events.usb_conn = true;
					if (!di->events.ac_conn)
						ab8500_btemp_periodic(di, true);
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {TYPE_3__* desc; int /*<<< orphan*/  num_supplicants; scalar_t__ supplied_to; } ;
struct device {int dummy; } ;
struct abx500_battery_type {int charge_full_design; int /*<<< orphan*/  nominal_voltage; } ;
struct TYPE_8__ {int charging; int fully_charged; int force_full; int batt_id_received; int batt_unknown; } ;
struct TYPE_6__ {int max_mah; int mah; int max_mah_design; } ;
struct ab8500_fg {int /*<<< orphan*/  bat_temp; TYPE_4__ flags; int /*<<< orphan*/  vbat_nom; TYPE_2__ bat_cap; TYPE_1__* bm; int /*<<< orphan*/  fg_work; int /*<<< orphan*/  fg_wq; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_7__ {int num_properties; int* properties; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {size_t batt_id; struct abx500_battery_type* bat_type; int /*<<< orphan*/  capacity_scaling; } ;

/* Variables and functions */
 size_t BATTERY_UNKNOWN ; 
 int MILLI_TO_MICRO ; 
#define  POWER_SUPPLY_PROP_STATUS 136 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 135 
#define  POWER_SUPPLY_PROP_TEMP 134 
#define  POWER_SUPPLY_STATUS_CHARGING 133 
#define  POWER_SUPPLY_STATUS_DISCHARGING 132 
#define  POWER_SUPPLY_STATUS_FULL 131 
#define  POWER_SUPPLY_STATUS_NOT_CHARGING 130 
#define  POWER_SUPPLY_STATUS_UNKNOWN 129 
#define  POWER_SUPPLY_TYPE_BATTERY 128 
 int /*<<< orphan*/  ab8500_fg_update_cap_scalers (struct ab8500_fg*) ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 int match_string (char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ab8500_fg* power_supply_get_drvdata (struct power_supply*) ; 
 scalar_t__ power_supply_get_property (struct power_supply*,int,union power_supply_propval*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ab8500_fg_get_ext_psy_data(struct device *dev, void *data)
{
	struct power_supply *psy;
	struct power_supply *ext = dev_get_drvdata(dev);
	const char **supplicants = (const char **)ext->supplied_to;
	struct ab8500_fg *di;
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
		case POWER_SUPPLY_PROP_STATUS:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_BATTERY:
				switch (ret.intval) {
				case POWER_SUPPLY_STATUS_UNKNOWN:
				case POWER_SUPPLY_STATUS_DISCHARGING:
				case POWER_SUPPLY_STATUS_NOT_CHARGING:
					if (!di->flags.charging)
						break;
					di->flags.charging = false;
					di->flags.fully_charged = false;
					if (di->bm->capacity_scaling)
						ab8500_fg_update_cap_scalers(di);
					queue_work(di->fg_wq, &di->fg_work);
					break;
				case POWER_SUPPLY_STATUS_FULL:
					if (di->flags.fully_charged)
						break;
					di->flags.fully_charged = true;
					di->flags.force_full = true;
					/* Save current capacity as maximum */
					di->bat_cap.max_mah = di->bat_cap.mah;
					queue_work(di->fg_wq, &di->fg_work);
					break;
				case POWER_SUPPLY_STATUS_CHARGING:
					if (di->flags.charging &&
						!di->flags.fully_charged)
						break;
					di->flags.charging = true;
					di->flags.fully_charged = false;
					if (di->bm->capacity_scaling)
						ab8500_fg_update_cap_scalers(di);
					queue_work(di->fg_wq, &di->fg_work);
					break;
				};
			default:
				break;
			};
			break;
		case POWER_SUPPLY_PROP_TECHNOLOGY:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_BATTERY:
				if (!di->flags.batt_id_received &&
				    di->bm->batt_id != BATTERY_UNKNOWN) {
					const struct abx500_battery_type *b;

					b = &(di->bm->bat_type[di->bm->batt_id]);

					di->flags.batt_id_received = true;

					di->bat_cap.max_mah_design =
						MILLI_TO_MICRO *
						b->charge_full_design;

					di->bat_cap.max_mah =
						di->bat_cap.max_mah_design;

					di->vbat_nom = b->nominal_voltage;
				}

				if (ret.intval)
					di->flags.batt_unknown = false;
				else
					di->flags.batt_unknown = true;
				break;
			default:
				break;
			}
			break;
		case POWER_SUPPLY_PROP_TEMP:
			switch (ext->desc->type) {
			case POWER_SUPPLY_TYPE_BATTERY:
				if (di->flags.batt_id_received)
					di->bat_temp = ret.intval;
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
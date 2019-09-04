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
union power_supply_propval {int intval; int /*<<< orphan*/  member_0; } ;
struct psy_am_i_supplied_data {int /*<<< orphan*/  count; int /*<<< orphan*/  psy; } ;
struct power_supply {TYPE_1__* desc; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_property ) (struct power_supply*,int /*<<< orphan*/ ,union power_supply_propval*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  POWER_SUPPLY_PROP_ONLINE ; 
 scalar_t__ __power_supply_is_supplied_by (struct power_supply*,int /*<<< orphan*/ ) ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct power_supply*,int /*<<< orphan*/ ,union power_supply_propval*) ; 

__attribute__((used)) static int __power_supply_am_i_supplied(struct device *dev, void *_data)
{
	union power_supply_propval ret = {0,};
	struct power_supply *epsy = dev_get_drvdata(dev);
	struct psy_am_i_supplied_data *data = _data;

	if (__power_supply_is_supplied_by(epsy, data->psy)) {
		data->count++;
		if (!epsy->desc->get_property(epsy, POWER_SUPPLY_PROP_ONLINE,
					&ret))
			return ret.intval;
	}

	return 0;
}
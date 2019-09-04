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
struct power_supply {TYPE_1__* desc; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* external_power_changed ) (struct power_supply*) ;} ;

/* Variables and functions */
 scalar_t__ __power_supply_is_supplied_by (struct power_supply*,struct power_supply*) ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct power_supply*) ; 

__attribute__((used)) static int __power_supply_changed_work(struct device *dev, void *data)
{
	struct power_supply *psy = data;
	struct power_supply *pst = dev_get_drvdata(dev);

	if (__power_supply_is_supplied_by(psy, pst)) {
		if (pst->desc->external_power_changed)
			pst->desc->external_power_changed(pst);
	}

	return 0;
}
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
typedef  union power_supply_propval {int dummy; } power_supply_propval ;
struct power_supply {TYPE_1__* desc; int /*<<< orphan*/  initialized; int /*<<< orphan*/  use_cnt; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {int (* get_property ) (struct power_supply*,int,union power_supply_propval*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int stub1 (struct power_supply*,int,union power_supply_propval*) ; 

int power_supply_get_property(struct power_supply *psy,
			    enum power_supply_property psp,
			    union power_supply_propval *val)
{
	if (atomic_read(&psy->use_cnt) <= 0) {
		if (!psy->initialized)
			return -EAGAIN;
		return -ENODEV;
	}

	return psy->desc->get_property(psy, psp, val);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_type {int /*<<< orphan*/  groups; } ;
struct TYPE_3__ {int /*<<< orphan*/  attr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/ ** __power_supply_attrs ; 
 int /*<<< orphan*/  power_supply_attr_groups ; 
 TYPE_1__* power_supply_attrs ; 

void power_supply_init_attrs(struct device_type *dev_type)
{
	int i;

	dev_type->groups = power_supply_attr_groups;

	for (i = 0; i < ARRAY_SIZE(power_supply_attrs); i++)
		__power_supply_attrs[i] = &power_supply_attrs[i].attr;
}
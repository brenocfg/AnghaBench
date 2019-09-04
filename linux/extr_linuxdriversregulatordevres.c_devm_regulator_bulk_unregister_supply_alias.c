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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_regulator_unregister_supply_alias (struct device*,char const* const) ; 

void devm_regulator_bulk_unregister_supply_alias(struct device *dev,
						 const char *const *id,
						 int num_id)
{
	int i;

	for (i = 0; i < num_id; ++i)
		devm_regulator_unregister_supply_alias(dev, id[i]);
}
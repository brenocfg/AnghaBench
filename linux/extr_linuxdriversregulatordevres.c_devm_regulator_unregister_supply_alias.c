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
struct regulator_supply_alias_match {char const* id; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devm_regulator_destroy_supply_alias ; 
 int /*<<< orphan*/  devm_regulator_match_supply_alias ; 
 int devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regulator_supply_alias_match*) ; 

void devm_regulator_unregister_supply_alias(struct device *dev, const char *id)
{
	struct regulator_supply_alias_match match;
	int rc;

	match.dev = dev;
	match.id = id;

	rc = devres_release(dev, devm_regulator_destroy_supply_alias,
			    devm_regulator_match_supply_alias, &match);
	if (rc != 0)
		WARN_ON(rc);
}
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
struct regulator_notifier_match {struct notifier_block* nb; struct regulator* regulator; } ;
struct regulator {int /*<<< orphan*/  dev; } ;
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devm_regulator_destroy_notifier ; 
 int /*<<< orphan*/  devm_regulator_match_notifier ; 
 int devres_release (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regulator_notifier_match*) ; 

void devm_regulator_unregister_notifier(struct regulator *regulator,
					struct notifier_block *nb)
{
	struct regulator_notifier_match match;
	int rc;

	match.regulator = regulator;
	match.nb = nb;

	rc = devres_release(regulator->dev, devm_regulator_destroy_notifier,
			    devm_regulator_match_notifier, &match);
	if (rc != 0)
		WARN_ON(rc);
}
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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_regulator_destroy_notifier ; 
 int /*<<< orphan*/  devres_add (int /*<<< orphan*/ ,struct regulator_notifier_match*) ; 
 struct regulator_notifier_match* devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct regulator_notifier_match*) ; 
 int regulator_register_notifier (struct regulator*,struct notifier_block*) ; 

int devm_regulator_register_notifier(struct regulator *regulator,
				     struct notifier_block *nb)
{
	struct regulator_notifier_match *match;
	int ret;

	match = devres_alloc(devm_regulator_destroy_notifier,
			     sizeof(struct regulator_notifier_match),
			     GFP_KERNEL);
	if (!match)
		return -ENOMEM;

	match->regulator = regulator;
	match->nb = nb;

	ret = regulator_register_notifier(regulator, nb);
	if (ret < 0) {
		devres_free(match);
		return ret;
	}

	devres_add(regulator->dev, match);

	return 0;
}
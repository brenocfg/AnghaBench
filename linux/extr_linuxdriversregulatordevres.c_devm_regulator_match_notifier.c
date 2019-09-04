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
struct regulator_notifier_match {scalar_t__ regulator; scalar_t__ nb; } ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int devm_regulator_match_notifier(struct device *dev, void *res,
					 void *data)
{
	struct regulator_notifier_match *match = res;
	struct regulator_notifier_match *target = data;

	return match->regulator == target->regulator && match->nb == target->nb;
}
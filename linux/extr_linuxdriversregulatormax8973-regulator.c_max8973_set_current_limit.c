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
struct regulator_dev {int dummy; } ;
struct max8973_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 unsigned int MAX8973_CKKADV_TRIP_150mV_PER_US ; 
 unsigned int MAX8973_CKKADV_TRIP_75mV_PER_US ; 
 unsigned int MAX8973_CKKADV_TRIP_DISABLE ; 
 int /*<<< orphan*/  MAX8973_CKKADV_TRIP_MASK ; 
 int /*<<< orphan*/  MAX8973_CONTROL2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct max8973_chip* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int max8973_set_current_limit(struct regulator_dev *rdev,
		int min_ua, int max_ua)
{
	struct max8973_chip *max = rdev_get_drvdata(rdev);
	unsigned int val;
	int ret;

	if (max_ua <= 9000000)
		val = MAX8973_CKKADV_TRIP_75mV_PER_US;
	else if (max_ua <= 12000000)
		val = MAX8973_CKKADV_TRIP_150mV_PER_US;
	else
		val = MAX8973_CKKADV_TRIP_DISABLE;

	ret = regmap_update_bits(max->regmap, MAX8973_CONTROL2,
			MAX8973_CKKADV_TRIP_MASK, val);
	if (ret < 0) {
		dev_err(max->dev, "register %d update failed: %d\n",
				MAX8973_CONTROL2, ret);
		return ret;
	}
	return 0;
}
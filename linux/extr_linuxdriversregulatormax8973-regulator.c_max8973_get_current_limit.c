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
#define  MAX8973_CKKADV_TRIP_150mV_PER_US 130 
#define  MAX8973_CKKADV_TRIP_75mV_PER_US 129 
#define  MAX8973_CKKADV_TRIP_DISABLE 128 
 unsigned int MAX8973_CKKADV_TRIP_MASK ; 
 int /*<<< orphan*/  MAX8973_CONTROL2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct max8973_chip* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max8973_get_current_limit(struct regulator_dev *rdev)
{
	struct max8973_chip *max = rdev_get_drvdata(rdev);
	unsigned int control2;
	int ret;

	ret = regmap_read(max->regmap, MAX8973_CONTROL2, &control2);
	if (ret < 0) {
		dev_err(max->dev, "register %d read failed: %d\n",
				MAX8973_CONTROL2, ret);
		return ret;
	}
	switch (control2 & MAX8973_CKKADV_TRIP_MASK) {
	case MAX8973_CKKADV_TRIP_DISABLE:
		return 15000000;
	case MAX8973_CKKADV_TRIP_150mV_PER_US:
		return 12000000;
	case MAX8973_CKKADV_TRIP_75mV_PER_US:
		return 9000000;
	default:
		break;
	}
	return 9000000;
}
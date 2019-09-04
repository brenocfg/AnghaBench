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
struct regulator_dev {int /*<<< orphan*/  regmap; } ;
struct hi655x_regulator {int /*<<< orphan*/  ctrl_mask; int /*<<< orphan*/  status_reg; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 struct hi655x_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int hi655x_is_enabled(struct regulator_dev *rdev)
{
	unsigned int value = 0;

	struct hi655x_regulator *regulator = rdev_get_drvdata(rdev);

	regmap_read(rdev->regmap, regulator->status_reg, &value);
	return (value & BIT(regulator->ctrl_mask));
}
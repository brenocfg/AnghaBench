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
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  enable_mask; } ;

/* Variables and functions */
 int ENOTRECOVERABLE ; 
 int MAX_FET_ENABLE_TRIES ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tps65090_try_enable_fet (struct regulator_dev*) ; 

__attribute__((used)) static int tps65090_fet_enable(struct regulator_dev *rdev)
{
	int ret, tries;

	/*
	 * Try enabling multiple times until we succeed since sometimes the
	 * first try times out.
	 */
	tries = 0;
	while (true) {
		ret = tps65090_try_enable_fet(rdev);
		if (!ret)
			break;
		if (ret != -ENOTRECOVERABLE || tries == MAX_FET_ENABLE_TRIES)
			goto err;

		/* Try turning the FET off (and then on again) */
		ret = regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
					 rdev->desc->enable_mask, 0);
		if (ret)
			goto err;

		tries++;
	}

	if (tries)
		dev_warn(&rdev->dev, "reg %#x enable ok after %d tries\n",
			 rdev->desc->enable_reg, tries);

	return 0;
err:
	dev_warn(&rdev->dev, "reg %#x enable failed\n", rdev->desc->enable_reg);
	WARN_ON(1);

	return ret;
}
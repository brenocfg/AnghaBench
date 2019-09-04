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
struct pv88090_regulator {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 unsigned int PV88090_BUCK1_MODE_MASK ; 
#define  PV88090_BUCK_MODE_AUTO 130 
#define  PV88090_BUCK_MODE_SLEEP 129 
#define  PV88090_BUCK_MODE_SYNC 128 
 int REGULATOR_MODE_FAST ; 
 int REGULATOR_MODE_NORMAL ; 
 int REGULATOR_MODE_STANDBY ; 
 struct pv88090_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static unsigned int pv88090_buck_get_mode(struct regulator_dev *rdev)
{
	struct pv88090_regulator *info = rdev_get_drvdata(rdev);
	unsigned int data;
	int ret, mode = 0;

	ret = regmap_read(rdev->regmap, info->conf, &data);
	if (ret < 0)
		return ret;

	switch (data & PV88090_BUCK1_MODE_MASK) {
	case PV88090_BUCK_MODE_SYNC:
		mode = REGULATOR_MODE_FAST;
		break;
	case PV88090_BUCK_MODE_AUTO:
		mode = REGULATOR_MODE_NORMAL;
		break;
	case PV88090_BUCK_MODE_SLEEP:
		mode = REGULATOR_MODE_STANDBY;
		break;
	}

	return mode;
}
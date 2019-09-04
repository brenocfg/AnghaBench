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
struct regulator_dev {TYPE_1__* desc; } ;
struct ltc3589 {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int apply_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTC3589_VCCR ; 
 unsigned int REGULATOR_MODE_STANDBY ; 
 struct ltc3589* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ltc3589_set_suspend_mode(struct regulator_dev *rdev,
				    unsigned int mode)
{
	struct ltc3589 *ltc3589 = rdev_get_drvdata(rdev);
	int mask, bit = 0;

	/* VCCR reference selects are right next to the VCCR go bits */
	mask = rdev->desc->apply_bit << 1;

	if (mode == REGULATOR_MODE_STANDBY)
		bit = mask;	/* Select DTV2 */

	mask |= rdev->desc->apply_bit;
	bit |= rdev->desc->apply_bit;
	return regmap_update_bits(ltc3589->regmap, LTC3589_VCCR, mask, bit);
}
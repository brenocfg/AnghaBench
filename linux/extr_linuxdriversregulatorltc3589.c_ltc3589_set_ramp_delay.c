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
struct TYPE_2__ {int /*<<< orphan*/  apply_bit; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LTC3589_VRRCR ; 
 int ffs (int /*<<< orphan*/ ) ; 
 struct ltc3589* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ltc3589_set_ramp_delay(struct regulator_dev *rdev, int ramp_delay)
{
	struct ltc3589 *ltc3589 = rdev_get_drvdata(rdev);
	int sel, shift;

	if (unlikely(ramp_delay <= 0))
		return -EINVAL;

	/* VRRCR slew rate offsets are the same as VCCR go bit offsets */
	shift = ffs(rdev->desc->apply_bit) - 1;

	/* The slew rate can be set to 0.88, 1.75, 3.5, or 7 mV/uS */
	for (sel = 0; sel < 4; sel++) {
		if ((880 << sel) >= ramp_delay) {
			return regmap_update_bits(ltc3589->regmap,
						  LTC3589_VRRCR,
						  0x3 << shift, sel << shift);
		}
	}
	return -EINVAL;
}
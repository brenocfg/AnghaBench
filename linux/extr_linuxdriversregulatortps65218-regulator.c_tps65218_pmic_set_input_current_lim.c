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
struct tps65218 {int dummy; } ;
struct regulator_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  csel_mask; int /*<<< orphan*/  csel_reg; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  TPS65218_PROTECT_L1 ; 
 int* ls3_currents ; 
 struct tps65218* rdev_get_drvdata (struct regulator_dev*) ; 
 int tps65218_set_bits (struct tps65218*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65218_pmic_set_input_current_lim(struct regulator_dev *dev,
					       int lim_uA)
{
	unsigned int index = 0;
	unsigned int num_currents = ARRAY_SIZE(ls3_currents);
	struct tps65218 *tps = rdev_get_drvdata(dev);

	while (index < num_currents && ls3_currents[index] != lim_uA)
		index++;

	if (index == num_currents)
		return -EINVAL;

	return tps65218_set_bits(tps, dev->desc->csel_reg, dev->desc->csel_mask,
				 index << 2, TPS65218_PROTECT_L1);
}
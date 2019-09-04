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
struct TYPE_2__ {int /*<<< orphan*/  bypass_mask; int /*<<< orphan*/  bypass_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int TPS65218_DCDC_1 ; 
 unsigned int TPS65218_LDO_1 ; 
 int /*<<< orphan*/  TPS65218_PROTECT_L1 ; 
 struct tps65218* rdev_get_drvdata (struct regulator_dev*) ; 
 unsigned int rdev_get_id (struct regulator_dev*) ; 
 int tps65218_clear_bits (struct tps65218*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps65218_pmic_set_suspend_enable(struct regulator_dev *dev)
{
	struct tps65218 *tps = rdev_get_drvdata(dev);
	unsigned int rid = rdev_get_id(dev);

	if (rid < TPS65218_DCDC_1 || rid > TPS65218_LDO_1)
		return -EINVAL;

	return tps65218_clear_bits(tps, dev->desc->bypass_reg,
				   dev->desc->bypass_mask,
				   TPS65218_PROTECT_L1);
}
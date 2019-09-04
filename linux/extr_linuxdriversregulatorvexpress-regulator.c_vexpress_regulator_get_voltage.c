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
typedef  int u32 ;
struct vexpress_regulator {int /*<<< orphan*/  regmap; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 struct vexpress_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int vexpress_regulator_get_voltage(struct regulator_dev *regdev)
{
	struct vexpress_regulator *reg = rdev_get_drvdata(regdev);
	u32 uV;
	int err = regmap_read(reg->regmap, 0, &uV);

	return err ? err : uV;
}
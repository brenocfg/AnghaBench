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
struct tps6524x {int dummy; } ;
struct supply_info {int /*<<< orphan*/  enable; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 struct tps6524x* rdev_get_drvdata (struct regulator_dev*) ; 
 size_t rdev_get_id (struct regulator_dev*) ; 
 struct supply_info* supply_info ; 
 int write_field (struct tps6524x*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int enable_supply(struct regulator_dev *rdev)
{
	const struct supply_info *info;
	struct tps6524x *hw;

	hw	= rdev_get_drvdata(rdev);
	info	= &supply_info[rdev_get_id(rdev)];

	return write_field(hw, &info->enable, 1);
}
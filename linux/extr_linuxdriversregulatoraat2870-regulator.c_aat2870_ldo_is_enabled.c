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
typedef  int u8 ;
struct regulator_dev {int dummy; } ;
struct aat2870_regulator {int enable_mask; int /*<<< orphan*/  enable_addr; struct aat2870_data* aat2870; } ;
struct aat2870_data {int (* read ) (struct aat2870_data*,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 struct aat2870_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int stub1 (struct aat2870_data*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int aat2870_ldo_is_enabled(struct regulator_dev *rdev)
{
	struct aat2870_regulator *ri = rdev_get_drvdata(rdev);
	struct aat2870_data *aat2870 = ri->aat2870;
	u8 val;
	int ret;

	ret = aat2870->read(aat2870, ri->enable_addr, &val);
	if (ret)
		return ret;

	return val & ri->enable_mask ? 1 : 0;
}
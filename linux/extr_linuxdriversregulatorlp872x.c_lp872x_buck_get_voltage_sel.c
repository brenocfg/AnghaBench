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
struct lp872x {int dummy; } ;
typedef  enum lp872x_regulator_id { ____Placeholder_lp872x_regulator_id } lp872x_regulator_id ;

/* Variables and functions */
 int EINVAL ; 
 int LP872X_VOUT_M ; 
 int /*<<< orphan*/  lp872x_is_valid_buck_addr (int) ; 
 int lp872x_read_byte (struct lp872x*,int,int*) ; 
 int lp872x_select_buck_vout_addr (struct lp872x*,int) ; 
 struct lp872x* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp872x_buck_get_voltage_sel(struct regulator_dev *rdev)
{
	struct lp872x *lp = rdev_get_drvdata(rdev);
	enum lp872x_regulator_id buck = rdev_get_id(rdev);
	u8 addr, val;
	int ret;

	addr = lp872x_select_buck_vout_addr(lp, buck);
	if (!lp872x_is_valid_buck_addr(addr))
		return -EINVAL;

	ret = lp872x_read_byte(lp, addr, &val);
	if (ret)
		return ret;

	return val & LP872X_VOUT_M;
}
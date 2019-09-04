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
typedef  size_t u8 ;
struct regulator_dev {int dummy; } ;
struct lp872x {int dummy; } ;
typedef  enum lp872x_regulator_id { ____Placeholder_lp872x_regulator_id } lp872x_regulator_id ;

/* Variables and functions */
 size_t ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 size_t LP8725_BUCK1_VOUT2 ; 
 size_t LP8725_BUCK2_VOUT2 ; 
 size_t LP8725_BUCK_CL_M ; 
 size_t LP8725_BUCK_CL_S ; 
#define  LP8725_ID_BUCK1 129 
#define  LP8725_ID_BUCK2 128 
 int* lp8725_buck_uA ; 
 int lp872x_read_byte (struct lp872x*,size_t,size_t*) ; 
 struct lp872x* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp8725_buck_get_current_limit(struct regulator_dev *rdev)
{
	struct lp872x *lp = rdev_get_drvdata(rdev);
	enum lp872x_regulator_id buck = rdev_get_id(rdev);
	u8 addr, val;
	int ret;

	switch (buck) {
	case LP8725_ID_BUCK1:
		addr = LP8725_BUCK1_VOUT2;
		break;
	case LP8725_ID_BUCK2:
		addr = LP8725_BUCK2_VOUT2;
		break;
	default:
		return -EINVAL;
	}

	ret = lp872x_read_byte(lp, addr, &val);
	if (ret)
		return ret;

	val = (val & LP8725_BUCK_CL_M) >> LP8725_BUCK_CL_S;

	return (val < ARRAY_SIZE(lp8725_buck_uA)) ?
			lp8725_buck_uA[val] : -EINVAL;
}
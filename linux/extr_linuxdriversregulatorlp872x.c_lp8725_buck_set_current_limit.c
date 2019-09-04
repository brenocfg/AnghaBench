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
typedef  int /*<<< orphan*/  u8 ;
struct regulator_dev {int dummy; } ;
struct lp872x {int dummy; } ;
typedef  enum lp872x_regulator_id { ____Placeholder_lp872x_regulator_id } lp872x_regulator_id ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LP8725_BUCK1_VOUT2 ; 
 int /*<<< orphan*/  LP8725_BUCK2_VOUT2 ; 
 int /*<<< orphan*/  LP8725_BUCK_CL_M ; 
 int LP8725_BUCK_CL_S ; 
#define  LP8725_ID_BUCK1 129 
#define  LP8725_ID_BUCK2 128 
 int* lp8725_buck_uA ; 
 int lp872x_update_bits (struct lp872x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct lp872x* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp8725_buck_set_current_limit(struct regulator_dev *rdev,
					int min_uA, int max_uA)
{
	struct lp872x *lp = rdev_get_drvdata(rdev);
	enum lp872x_regulator_id buck = rdev_get_id(rdev);
	int i;
	u8 addr;

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

	for (i = ARRAY_SIZE(lp8725_buck_uA) - 1; i >= 0; i--) {
		if (lp8725_buck_uA[i] >= min_uA &&
			lp8725_buck_uA[i] <= max_uA)
			return lp872x_update_bits(lp, addr,
						  LP8725_BUCK_CL_M,
						  i << LP8725_BUCK_CL_S);
	}

	return -EINVAL;
}
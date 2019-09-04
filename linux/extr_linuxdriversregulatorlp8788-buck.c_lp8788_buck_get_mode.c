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
struct lp8788_buck {int /*<<< orphan*/  lp; } ;
typedef  enum lp8788_buck_id { ____Placeholder_lp8788_buck_id } lp8788_buck_id ;

/* Variables and functions */
 int BUCK_FPWM_MASK (int) ; 
 int /*<<< orphan*/  LP8788_BUCK_PWM ; 
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 int lp8788_read_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct lp8788_buck* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static unsigned int lp8788_buck_get_mode(struct regulator_dev *rdev)
{
	struct lp8788_buck *buck = rdev_get_drvdata(rdev);
	enum lp8788_buck_id id = rdev_get_id(rdev);
	u8 val;
	int ret;

	ret = lp8788_read_byte(buck->lp, LP8788_BUCK_PWM, &val);
	if (ret)
		return ret;

	return val & BUCK_FPWM_MASK(id) ?
				REGULATOR_MODE_FAST : REGULATOR_MODE_NORMAL;
}
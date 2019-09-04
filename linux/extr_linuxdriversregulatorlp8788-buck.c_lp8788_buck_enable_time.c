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
 int EINVAL ; 
 int ENABLE_TIME_USEC ; 
 int LP8788_BUCK1_TIMESTEP ; 
 int LP8788_STARTUP_TIME_M ; 
 int LP8788_STARTUP_TIME_S ; 
 scalar_t__ lp8788_read_byte (int /*<<< orphan*/ ,int,int*) ; 
 struct lp8788_buck* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp8788_buck_enable_time(struct regulator_dev *rdev)
{
	struct lp8788_buck *buck = rdev_get_drvdata(rdev);
	enum lp8788_buck_id id = rdev_get_id(rdev);
	u8 val, addr = LP8788_BUCK1_TIMESTEP + id;

	if (lp8788_read_byte(buck->lp, addr, &val))
		return -EINVAL;

	val = (val & LP8788_STARTUP_TIME_M) >> LP8788_STARTUP_TIME_S;

	return ENABLE_TIME_USEC * val;
}
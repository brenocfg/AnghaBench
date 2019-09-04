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
struct rpmh_vreg {unsigned int mode; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 struct rpmh_vreg* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static unsigned int rpmh_regulator_vrm_get_mode(struct regulator_dev *rdev)
{
	struct rpmh_vreg *vreg = rdev_get_drvdata(rdev);

	return vreg->mode;
}
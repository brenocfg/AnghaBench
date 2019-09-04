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
struct rpmh_vreg {TYPE_1__* hw_data; } ;
struct regulator_dev {int dummy; } ;
struct TYPE_2__ {int hpm_min_load_uA; } ;

/* Variables and functions */
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 struct rpmh_vreg* rdev_get_drvdata (struct regulator_dev*) ; 
 int rpmh_regulator_vrm_set_mode (struct regulator_dev*,unsigned int) ; 

__attribute__((used)) static int rpmh_regulator_vrm_set_load(struct regulator_dev *rdev, int load_uA)
{
	struct rpmh_vreg *vreg = rdev_get_drvdata(rdev);
	unsigned int mode;

	if (load_uA >= vreg->hw_data->hpm_min_load_uA)
		mode = REGULATOR_MODE_NORMAL;
	else
		mode = REGULATOR_MODE_IDLE;

	return rpmh_regulator_vrm_set_mode(rdev, mode);
}
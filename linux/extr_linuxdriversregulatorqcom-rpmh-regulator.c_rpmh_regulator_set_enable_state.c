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
struct tcs_cmd {int data; scalar_t__ addr; } ;
struct rpmh_vreg {int enabled; int /*<<< orphan*/  voltage_selector; scalar_t__ addr; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ENOTRECOVERABLE ; 
 scalar_t__ RPMH_REGULATOR_REG_ENABLE ; 
 int _rpmh_regulator_vrm_set_voltage_sel (struct regulator_dev*,int /*<<< orphan*/ ,int) ; 
 struct rpmh_vreg* rdev_get_drvdata (struct regulator_dev*) ; 
 int rpmh_regulator_send_request (struct rpmh_vreg*,struct tcs_cmd*,int) ; 

__attribute__((used)) static int rpmh_regulator_set_enable_state(struct regulator_dev *rdev,
					bool enable)
{
	struct rpmh_vreg *vreg = rdev_get_drvdata(rdev);
	struct tcs_cmd cmd = {
		.addr = vreg->addr + RPMH_REGULATOR_REG_ENABLE,
		.data = enable,
	};
	int ret;

	if (vreg->enabled == -EINVAL &&
	    vreg->voltage_selector != -ENOTRECOVERABLE) {
		ret = _rpmh_regulator_vrm_set_voltage_sel(rdev,
						vreg->voltage_selector, true);
		if (ret < 0)
			return ret;
	}

	ret = rpmh_regulator_send_request(vreg, &cmd, enable);
	if (!ret)
		vreg->enabled = enable;

	return ret;
}
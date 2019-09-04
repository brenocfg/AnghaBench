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
struct tcs_cmd {int data; scalar_t__ addr; } ;
struct rpmh_vreg {TYPE_1__* hw_data; scalar_t__ addr; } ;
struct TYPE_2__ {int* pmic_mode_map; } ;

/* Variables and functions */
 int EINVAL ; 
 int PMIC4_BOB_MODE_PASS ; 
 unsigned int REGULATOR_MODE_STANDBY ; 
 scalar_t__ RPMH_REGULATOR_REG_VRM_MODE ; 
 int rpmh_regulator_send_request (struct rpmh_vreg*,struct tcs_cmd*,int) ; 

__attribute__((used)) static int rpmh_regulator_vrm_set_mode_bypass(struct rpmh_vreg *vreg,
					unsigned int mode, bool bypassed)
{
	struct tcs_cmd cmd = {
		.addr = vreg->addr + RPMH_REGULATOR_REG_VRM_MODE,
	};
	int pmic_mode;

	if (mode > REGULATOR_MODE_STANDBY)
		return -EINVAL;

	pmic_mode = vreg->hw_data->pmic_mode_map[mode];
	if (pmic_mode < 0)
		return pmic_mode;

	if (bypassed)
		cmd.data = PMIC4_BOB_MODE_PASS;
	else
		cmd.data = pmic_mode;

	return rpmh_regulator_send_request(vreg, &cmd, true);
}
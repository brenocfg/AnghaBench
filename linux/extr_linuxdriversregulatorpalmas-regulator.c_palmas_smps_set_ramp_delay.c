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
struct regulator_dev {int dummy; } ;
struct palmas_regs_info {int /*<<< orphan*/  tstep_addr; } ;
struct palmas_pmic_driver_data {struct palmas_regs_info* palmas_regs_info; } ;
struct palmas_pmic {int /*<<< orphan*/ * ramp_delay; TYPE_1__* palmas; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; struct palmas_pmic_driver_data* pmic_ddata; } ;

/* Variables and functions */
#define  PALMAS_REG_SMPS3 129 
#define  PALMAS_REG_SMPS7 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * palmas_smps_ramp_delay ; 
 int palmas_smps_write (TYPE_1__*,int /*<<< orphan*/ ,unsigned int) ; 
 struct palmas_pmic* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int palmas_smps_set_ramp_delay(struct regulator_dev *rdev,
		 int ramp_delay)
{
	int id = rdev_get_id(rdev);
	struct palmas_pmic *pmic = rdev_get_drvdata(rdev);
	struct palmas_pmic_driver_data *ddata = pmic->palmas->pmic_ddata;
	struct palmas_regs_info *rinfo = &ddata->palmas_regs_info[id];
	unsigned int reg = 0;
	int ret;

	/* SMPS3 and SMPS7 do not have tstep_addr setting */
	switch (id) {
	case PALMAS_REG_SMPS3:
	case PALMAS_REG_SMPS7:
		return 0;
	}

	if (ramp_delay <= 0)
		reg = 0;
	else if (ramp_delay <= 2500)
		reg = 3;
	else if (ramp_delay <= 5000)
		reg = 2;
	else
		reg = 1;

	ret = palmas_smps_write(pmic->palmas, rinfo->tstep_addr, reg);
	if (ret < 0) {
		dev_err(pmic->palmas->dev, "TSTEP write failed: %d\n", ret);
		return ret;
	}

	pmic->ramp_delay[id] = palmas_smps_ramp_delay[reg];
	return ret;
}
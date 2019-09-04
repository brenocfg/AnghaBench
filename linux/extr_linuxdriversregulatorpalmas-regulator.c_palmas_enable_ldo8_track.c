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
struct palmas_regs_info {unsigned int ctrl_addr; unsigned int vsel_addr; } ;
struct palmas_pmic_driver_data {struct palmas_regs_info* palmas_regs_info; } ;
struct palmas {int /*<<< orphan*/  dev; struct palmas_pmic_driver_data* pmic_ddata; } ;

/* Variables and functions */
 unsigned int PALMAS_LDO8_CTRL_LDO_TRACKING_EN ; 
 unsigned int PALMAS_LDO8_VOLTAGE_VSEL_MASK ; 
 size_t PALMAS_REG_LDO8 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int palmas_ldo_read (struct palmas*,unsigned int,unsigned int*) ; 
 int palmas_ldo_write (struct palmas*,unsigned int,unsigned int) ; 

__attribute__((used)) static void palmas_enable_ldo8_track(struct palmas *palmas)
{
	unsigned int reg;
	unsigned int addr;
	int ret;
	struct palmas_pmic_driver_data *ddata = palmas->pmic_ddata;
	struct palmas_regs_info *rinfo;

	rinfo = &ddata->palmas_regs_info[PALMAS_REG_LDO8];
	addr = rinfo->ctrl_addr;

	ret = palmas_ldo_read(palmas, addr, &reg);
	if (ret) {
		dev_err(palmas->dev, "Error in reading ldo8 control reg\n");
		return;
	}

	reg |= PALMAS_LDO8_CTRL_LDO_TRACKING_EN;
	ret = palmas_ldo_write(palmas, addr, reg);
	if (ret < 0) {
		dev_err(palmas->dev, "Error in enabling tracking mode\n");
		return;
	}
	/*
	 * When SMPS45 is set to off and LDO8 tracking is enabled, the LDO8
	 * output is defined by the LDO8_VOLTAGE.VSEL register divided by two,
	 * and can be set from 0.45 to 1.65 V.
	 */
	addr = rinfo->vsel_addr;
	ret = palmas_ldo_read(palmas, addr, &reg);
	if (ret) {
		dev_err(palmas->dev, "Error in reading ldo8 voltage reg\n");
		return;
	}

	reg = (reg << 1) & PALMAS_LDO8_VOLTAGE_VSEL_MASK;
	ret = palmas_ldo_write(palmas, addr, reg);
	if (ret < 0)
		dev_err(palmas->dev, "Error in setting ldo8 voltage reg\n");

	return;
}
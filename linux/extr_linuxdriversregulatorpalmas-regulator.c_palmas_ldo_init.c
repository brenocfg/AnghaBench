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
struct palmas_regs_info {unsigned int ctrl_addr; } ;
struct palmas_reg_init {scalar_t__ roof_floor; scalar_t__ mode_sleep; scalar_t__ warm_reset; } ;
struct palmas_pmic_driver_data {struct palmas_regs_info* palmas_regs_info; } ;
struct palmas {int /*<<< orphan*/  dev; struct palmas_pmic_driver_data* pmic_ddata; } ;

/* Variables and functions */
 int /*<<< orphan*/  PALMAS_LDO1_CTRL_MODE_ACTIVE ; 
 unsigned int PALMAS_LDO1_CTRL_MODE_SLEEP ; 
 unsigned int PALMAS_LDO1_CTRL_WR_S ; 
 int /*<<< orphan*/  PALMAS_LDO_BASE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int palmas_ldo_read (struct palmas*,unsigned int,unsigned int*) ; 
 int palmas_ldo_write (struct palmas*,unsigned int,unsigned int) ; 
 int palmas_regulator_config_external (struct palmas*,int,struct palmas_reg_init*) ; 
 int palmas_update_bits (struct palmas*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int palmas_ldo_init(struct palmas *palmas, int id,
		struct palmas_reg_init *reg_init)
{
	unsigned int reg;
	unsigned int addr;
	int ret;
	struct palmas_pmic_driver_data *ddata = palmas->pmic_ddata;
	struct palmas_regs_info *rinfo = &ddata->palmas_regs_info[id];

	addr = rinfo->ctrl_addr;

	ret = palmas_ldo_read(palmas, addr, &reg);
	if (ret)
		return ret;

	if (reg_init->warm_reset)
		reg |= PALMAS_LDO1_CTRL_WR_S;
	else
		reg &= ~PALMAS_LDO1_CTRL_WR_S;

	if (reg_init->mode_sleep)
		reg |= PALMAS_LDO1_CTRL_MODE_SLEEP;
	else
		reg &= ~PALMAS_LDO1_CTRL_MODE_SLEEP;

	ret = palmas_ldo_write(palmas, addr, reg);
	if (ret)
		return ret;

	if (reg_init->roof_floor) {
		/* Enable externally controlled regulator */
		ret = palmas_update_bits(palmas, PALMAS_LDO_BASE,
				addr, PALMAS_LDO1_CTRL_MODE_ACTIVE,
				PALMAS_LDO1_CTRL_MODE_ACTIVE);
		if (ret < 0) {
			dev_err(palmas->dev,
				"LDO Register 0x%02x update failed %d\n",
				addr, ret);
			return ret;
		}
		return palmas_regulator_config_external(palmas, id, reg_init);
	}
	return 0;
}
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
typedef  int uint8_t ;
struct tps51632_regulator_platform_data {scalar_t__ max_voltage_uV; scalar_t__ dvfs_step_20mV; scalar_t__ base_voltage_uV; int /*<<< orphan*/  enable_pwm_dvfs; } ;
struct tps51632_chip {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  TPS51632_DVFS_CONTROL_REG ; 
 int TPS51632_DVFS_PWMEN ; 
 int TPS51632_DVFS_STEP_20 ; 
 unsigned int TPS51632_VMAX_LOCK ; 
 int /*<<< orphan*/  TPS51632_VMAX_REG ; 
 int /*<<< orphan*/  TPS51632_VOLTAGE_BASE_REG ; 
 int TPS51632_VOLT_VSEL (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tps51632_init_dcdc(struct tps51632_chip *tps,
		struct tps51632_regulator_platform_data *pdata)
{
	int ret;
	uint8_t	control = 0;
	int vsel;

	if (!pdata->enable_pwm_dvfs)
		goto skip_pwm_config;

	control |= TPS51632_DVFS_PWMEN;
	vsel = TPS51632_VOLT_VSEL(pdata->base_voltage_uV);
	ret = regmap_write(tps->regmap, TPS51632_VOLTAGE_BASE_REG, vsel);
	if (ret < 0) {
		dev_err(tps->dev, "BASE reg write failed, err %d\n", ret);
		return ret;
	}

	if (pdata->dvfs_step_20mV)
		control |= TPS51632_DVFS_STEP_20;

	if (pdata->max_voltage_uV) {
		unsigned int vmax;
		/**
		 * TPS51632 hw behavior: VMAX register can be write only
		 * once as it get locked after first write. The lock get
		 * reset only when device is power-reset.
		 * Write register only when lock bit is not enabled.
		 */
		ret = regmap_read(tps->regmap, TPS51632_VMAX_REG, &vmax);
		if (ret < 0) {
			dev_err(tps->dev, "VMAX read failed, err %d\n", ret);
			return ret;
		}
		if (!(vmax & TPS51632_VMAX_LOCK)) {
			vsel = TPS51632_VOLT_VSEL(pdata->max_voltage_uV);
			ret = regmap_write(tps->regmap, TPS51632_VMAX_REG,
					vsel);
			if (ret < 0) {
				dev_err(tps->dev,
					"VMAX write failed, err %d\n", ret);
				return ret;
			}
		}
	}

skip_pwm_config:
	ret = regmap_write(tps->regmap, TPS51632_DVFS_CONTROL_REG, control);
	if (ret < 0)
		dev_err(tps->dev, "DVFS reg write failed, err %d\n", ret);
	return ret;
}
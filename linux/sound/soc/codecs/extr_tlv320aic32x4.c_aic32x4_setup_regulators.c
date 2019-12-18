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
struct device {int dummy; } ;
struct aic32x4_priv {void* supply_iov; void* supply_ldo; void* supply_dv; int /*<<< orphan*/  power_cfg; void* supply_av; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC32X4_PWR_AIC32X4_LDO_ENABLE ; 
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_regulator_get (struct device*,char*) ; 
 void* devm_regulator_get_optional (struct device*,char*) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 

__attribute__((used)) static int aic32x4_setup_regulators(struct device *dev,
		struct aic32x4_priv *aic32x4)
{
	int ret = 0;

	aic32x4->supply_ldo = devm_regulator_get_optional(dev, "ldoin");
	aic32x4->supply_iov = devm_regulator_get(dev, "iov");
	aic32x4->supply_dv = devm_regulator_get_optional(dev, "dv");
	aic32x4->supply_av = devm_regulator_get_optional(dev, "av");

	/* Check if the regulator requirements are fulfilled */

	if (IS_ERR(aic32x4->supply_iov)) {
		dev_err(dev, "Missing supply 'iov'\n");
		return PTR_ERR(aic32x4->supply_iov);
	}

	if (IS_ERR(aic32x4->supply_ldo)) {
		if (PTR_ERR(aic32x4->supply_ldo) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		if (IS_ERR(aic32x4->supply_dv)) {
			dev_err(dev, "Missing supply 'dv' or 'ldoin'\n");
			return PTR_ERR(aic32x4->supply_dv);
		}
		if (IS_ERR(aic32x4->supply_av)) {
			dev_err(dev, "Missing supply 'av' or 'ldoin'\n");
			return PTR_ERR(aic32x4->supply_av);
		}
	} else {
		if (IS_ERR(aic32x4->supply_dv) &&
				PTR_ERR(aic32x4->supply_dv) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
		if (IS_ERR(aic32x4->supply_av) &&
				PTR_ERR(aic32x4->supply_av) == -EPROBE_DEFER)
			return -EPROBE_DEFER;
	}

	ret = regulator_enable(aic32x4->supply_iov);
	if (ret) {
		dev_err(dev, "Failed to enable regulator iov\n");
		return ret;
	}

	if (!IS_ERR(aic32x4->supply_ldo)) {
		ret = regulator_enable(aic32x4->supply_ldo);
		if (ret) {
			dev_err(dev, "Failed to enable regulator ldo\n");
			goto error_ldo;
		}
	}

	if (!IS_ERR(aic32x4->supply_dv)) {
		ret = regulator_enable(aic32x4->supply_dv);
		if (ret) {
			dev_err(dev, "Failed to enable regulator dv\n");
			goto error_dv;
		}
	}

	if (!IS_ERR(aic32x4->supply_av)) {
		ret = regulator_enable(aic32x4->supply_av);
		if (ret) {
			dev_err(dev, "Failed to enable regulator av\n");
			goto error_av;
		}
	}

	if (!IS_ERR(aic32x4->supply_ldo) && IS_ERR(aic32x4->supply_av))
		aic32x4->power_cfg |= AIC32X4_PWR_AIC32X4_LDO_ENABLE;

	return 0;

error_av:
	if (!IS_ERR(aic32x4->supply_dv))
		regulator_disable(aic32x4->supply_dv);

error_dv:
	if (!IS_ERR(aic32x4->supply_ldo))
		regulator_disable(aic32x4->supply_ldo);

error_ldo:
	regulator_disable(aic32x4->supply_iov);
	return ret;
}
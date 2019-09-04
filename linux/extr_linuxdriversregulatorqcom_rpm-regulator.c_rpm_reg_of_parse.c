#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct regulator_desc {int dummy; } ;
struct regulator_config {struct device* dev; struct qcom_rpm_reg* driver_data; } ;
struct qcom_rpm_reg {TYPE_2__* parts; int /*<<< orphan*/  supports_force_mode_bypass; int /*<<< orphan*/  supports_force_mode_auto; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {scalar_t__ mask; } ;
struct TYPE_4__ {scalar_t__ mask; } ;
struct TYPE_5__ {TYPE_3__ fm; TYPE_3__ pm; TYPE_1__ freq; TYPE_3__ pd; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FORCE_MODE_IS_2_BITS (struct qcom_rpm_reg*) ; 
#define  QCOM_RPM_FORCE_MODE_AUTO 132 
#define  QCOM_RPM_FORCE_MODE_BYPASS 131 
#define  QCOM_RPM_FORCE_MODE_HPM 130 
#define  QCOM_RPM_FORCE_MODE_LPM 129 
#define  QCOM_RPM_FORCE_MODE_NONE 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char const*) ; 
 int of_property_read_u32 (struct device_node*,char const*,int*) ; 
 int rpm_reg_of_parse_freq (struct device*,struct device_node*,struct qcom_rpm_reg*) ; 
 int rpm_reg_set (struct qcom_rpm_reg*,TYPE_3__*,int) ; 

__attribute__((used)) static int rpm_reg_of_parse(struct device_node *node,
			    const struct regulator_desc *desc,
			    struct regulator_config *config)
{
	struct qcom_rpm_reg *vreg = config->driver_data;
	struct device *dev = config->dev;
	const char *key;
	u32 force_mode;
	bool pwm;
	u32 val;
	int ret;

	key = "bias-pull-down";
	if (of_property_read_bool(node, key)) {
		ret = rpm_reg_set(vreg, &vreg->parts->pd, 1);
		if (ret) {
			dev_err(dev, "%s is invalid", key);
			return ret;
		}
	}

	if (vreg->parts->freq.mask) {
		ret = rpm_reg_of_parse_freq(dev, node, vreg);
		if (ret < 0)
			return ret;
	}

	if (vreg->parts->pm.mask) {
		key = "qcom,power-mode-hysteretic";
		pwm = !of_property_read_bool(node, key);

		ret = rpm_reg_set(vreg, &vreg->parts->pm, pwm);
		if (ret) {
			dev_err(dev, "failed to set power mode\n");
			return ret;
		}
	}

	if (vreg->parts->fm.mask) {
		force_mode = -1;

		key = "qcom,force-mode";
		ret = of_property_read_u32(node, key, &val);
		if (ret == -EINVAL) {
			val = QCOM_RPM_FORCE_MODE_NONE;
		} else if (ret < 0) {
			dev_err(dev, "failed to read %s\n", key);
			return ret;
		}

		/*
		 * If force-mode is encoded as 2 bits then the
		 * possible register values are:
		 * NONE, LPM, HPM
		 * otherwise:
		 * NONE, LPM, AUTO, HPM, BYPASS
		 */
		switch (val) {
		case QCOM_RPM_FORCE_MODE_NONE:
			force_mode = 0;
			break;
		case QCOM_RPM_FORCE_MODE_LPM:
			force_mode = 1;
			break;
		case QCOM_RPM_FORCE_MODE_HPM:
			if (FORCE_MODE_IS_2_BITS(vreg))
				force_mode = 2;
			else
				force_mode = 3;
			break;
		case QCOM_RPM_FORCE_MODE_AUTO:
			if (vreg->supports_force_mode_auto)
				force_mode = 2;
			break;
		case QCOM_RPM_FORCE_MODE_BYPASS:
			if (vreg->supports_force_mode_bypass)
				force_mode = 4;
			break;
		}

		if (force_mode == -1) {
			dev_err(dev, "invalid force mode\n");
			return -EINVAL;
		}

		ret = rpm_reg_set(vreg, &vreg->parts->fm, force_mode);
		if (ret) {
			dev_err(dev, "failed to set force mode\n");
			return ret;
		}
	}

	return 0;
}
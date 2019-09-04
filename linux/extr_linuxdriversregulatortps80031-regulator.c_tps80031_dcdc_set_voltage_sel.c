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
typedef  int u8 ;
struct tps80031_regulator {TYPE_1__* rinfo; int /*<<< orphan*/  dev; } ;
struct regulator_dev {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {scalar_t__ volt_reg; int /*<<< orphan*/  volt_id; scalar_t__ force_reg; } ;

/* Variables and functions */
 int SMPS_CMD_MASK ; 
 int /*<<< orphan*/  SMPS_VSEL_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,int) ; 
 struct tps80031_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 struct device* to_tps80031_dev (struct regulator_dev*) ; 
 int tps80031_read (struct device*,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int tps80031_update (struct device*,int /*<<< orphan*/ ,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps80031_dcdc_set_voltage_sel(struct regulator_dev *rdev,
		unsigned vsel)
{
	struct tps80031_regulator *ri = rdev_get_drvdata(rdev);
	struct device *parent = to_tps80031_dev(rdev);
	int ret;
	u8 reg_val;

	if (ri->rinfo->force_reg) {
		ret = tps80031_read(parent, ri->rinfo->volt_id,
						ri->rinfo->force_reg, &reg_val);
		if (ret < 0) {
			dev_err(ri->dev, "reg 0x%02x read failed, e = %d\n",
				ri->rinfo->force_reg, ret);
			return ret;
		}
		if (!(reg_val & SMPS_CMD_MASK)) {
			ret = tps80031_update(parent, ri->rinfo->volt_id,
				ri->rinfo->force_reg, vsel, SMPS_VSEL_MASK);
			if (ret < 0)
				dev_err(ri->dev,
					"reg 0x%02x update failed, e = %d\n",
					ri->rinfo->force_reg, ret);
			return ret;
		}
	}
	ret = tps80031_update(parent, ri->rinfo->volt_id,
			ri->rinfo->volt_reg, vsel, SMPS_VSEL_MASK);
	if (ret < 0)
		dev_err(ri->dev, "reg 0x%02x update failed, e = %d\n",
			ri->rinfo->volt_reg, ret);
	return ret;
}
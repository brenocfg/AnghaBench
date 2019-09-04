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
struct tps80031_regulator {int /*<<< orphan*/  dev; } ;
struct regulator_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOST_HW_PWR_EN ; 
 int /*<<< orphan*/  OPA_MODE_EN ; 
 int /*<<< orphan*/  TPS80031_CHARGERUSB_CTRL1 ; 
 int /*<<< orphan*/  TPS80031_CHARGERUSB_CTRL3 ; 
 int /*<<< orphan*/  TPS80031_SLAVE_ID2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct tps80031_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 struct device* to_tps80031_dev (struct regulator_dev*) ; 
 int tps80031_set_bits (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tps80031_vbus_enable(struct regulator_dev *rdev)
{
	struct tps80031_regulator *ri = rdev_get_drvdata(rdev);
	struct device *parent = to_tps80031_dev(rdev);
	int ret;

	ret = tps80031_set_bits(parent, TPS80031_SLAVE_ID2,
				TPS80031_CHARGERUSB_CTRL1, OPA_MODE_EN);
	if (ret < 0) {
		dev_err(ri->dev, "reg 0x%02x read failed, e = %d\n",
					TPS80031_CHARGERUSB_CTRL1, ret);
		return ret;
	}

	ret = tps80031_set_bits(parent, TPS80031_SLAVE_ID2,
				TPS80031_CHARGERUSB_CTRL3, BOOST_HW_PWR_EN);
	if (ret < 0) {
		dev_err(ri->dev, "reg 0x%02x read failed, e = %d\n",
			TPS80031_CHARGERUSB_CTRL3, ret);
		return ret;
	}
	return ret;
}
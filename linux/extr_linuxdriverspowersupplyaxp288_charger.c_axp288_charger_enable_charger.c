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
struct axp288_chrg_info {TYPE_1__* pdev; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_CHRG_CTRL1 ; 
 int /*<<< orphan*/  CHRG_CCCV_CHG_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axp288_charger_enable_charger(struct axp288_chrg_info *info,
								bool enable)
{
	int ret;

	if (enable)
		ret = regmap_update_bits(info->regmap, AXP20X_CHRG_CTRL1,
				CHRG_CCCV_CHG_EN, CHRG_CCCV_CHG_EN);
	else
		ret = regmap_update_bits(info->regmap, AXP20X_CHRG_CTRL1,
				CHRG_CCCV_CHG_EN, 0);
	if (ret < 0)
		dev_err(&info->pdev->dev, "axp288 enable charger %d\n", ret);

	return ret;
}
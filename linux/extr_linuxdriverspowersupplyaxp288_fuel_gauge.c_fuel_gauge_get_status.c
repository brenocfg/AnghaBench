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
struct axp288_fg_info {void* status; TYPE_1__* pdev; int /*<<< orphan*/ * iio_channel; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_FG_RES ; 
 int /*<<< orphan*/  AXP20X_PWR_INPUT_STATUS ; 
 size_t BAT_D_CURR ; 
 int FG_REP_CAP_VALID ; 
 void* POWER_SUPPLY_STATUS_CHARGING ; 
 void* POWER_SUPPLY_STATUS_DISCHARGING ; 
 void* POWER_SUPPLY_STATUS_FULL ; 
 int PS_STAT_BAT_CHRG_DIR ; 
 int PS_STAT_VBUS_VALID ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int fuel_gauge_reg_readb (struct axp288_fg_info*,int /*<<< orphan*/ ) ; 
 int iio_read_channel_raw (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void fuel_gauge_get_status(struct axp288_fg_info *info)
{
	int pwr_stat, fg_res, curr, ret;

	pwr_stat = fuel_gauge_reg_readb(info, AXP20X_PWR_INPUT_STATUS);
	if (pwr_stat < 0) {
		dev_err(&info->pdev->dev,
			"PWR STAT read failed:%d\n", pwr_stat);
		return;
	}

	/* Report full if Vbus is valid and the reported capacity is 100% */
	if (!(pwr_stat & PS_STAT_VBUS_VALID))
		goto not_full;

	fg_res = fuel_gauge_reg_readb(info, AXP20X_FG_RES);
	if (fg_res < 0) {
		dev_err(&info->pdev->dev, "FG RES read failed: %d\n", fg_res);
		return;
	}
	if (!(fg_res & FG_REP_CAP_VALID))
		goto not_full;

	fg_res &= ~FG_REP_CAP_VALID;
	if (fg_res == 100) {
		info->status = POWER_SUPPLY_STATUS_FULL;
		return;
	}

	/*
	 * Sometimes the charger turns itself off before fg-res reaches 100%.
	 * When this happens the AXP288 reports a not-charging status and
	 * 0 mA discharge current.
	 */
	if (fg_res < 90 || (pwr_stat & PS_STAT_BAT_CHRG_DIR))
		goto not_full;

	ret = iio_read_channel_raw(info->iio_channel[BAT_D_CURR], &curr);
	if (ret < 0) {
		dev_err(&info->pdev->dev, "FG get current failed: %d\n", ret);
		return;
	}
	if (curr == 0) {
		info->status = POWER_SUPPLY_STATUS_FULL;
		return;
	}

not_full:
	if (pwr_stat & PS_STAT_BAT_CHRG_DIR)
		info->status = POWER_SUPPLY_STATUS_CHARGING;
	else
		info->status = POWER_SUPPLY_STATUS_DISCHARGING;
}
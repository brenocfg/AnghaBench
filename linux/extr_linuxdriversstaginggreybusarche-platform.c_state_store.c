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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct arche_platform_drvdata {scalar_t__ state; int /*<<< orphan*/  platform_state_mutex; int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ ARCHE_PLATFORM_STATE_ACTIVE ; 
 scalar_t__ ARCHE_PLATFORM_STATE_FW_FLASHING ; 
 scalar_t__ ARCHE_PLATFORM_STATE_OFF ; 
 scalar_t__ ARCHE_PLATFORM_STATE_STANDBY ; 
 int EINVAL ; 
 int /*<<< orphan*/  apb_poweroff ; 
 int arche_platform_coldboot_seq (struct arche_platform_drvdata*) ; 
 int arche_platform_fw_flashing_seq (struct arche_platform_drvdata*) ; 
 int /*<<< orphan*/  arche_platform_poweroff_seq (struct arche_platform_drvdata*) ; 
 int /*<<< orphan*/  arche_platform_wd_irq_en (struct arche_platform_drvdata*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct arche_platform_drvdata* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 

__attribute__((used)) static ssize_t state_store(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct arche_platform_drvdata *arche_pdata = dev_get_drvdata(dev);
	int ret = 0;

	mutex_lock(&arche_pdata->platform_state_mutex);

	if (sysfs_streq(buf, "off")) {
		if (arche_pdata->state == ARCHE_PLATFORM_STATE_OFF)
			goto exit;

		/*  If SVC goes down, bring down APB's as well */
		device_for_each_child(arche_pdata->dev, NULL, apb_poweroff);

		arche_platform_poweroff_seq(arche_pdata);

	} else if (sysfs_streq(buf, "active")) {
		if (arche_pdata->state == ARCHE_PLATFORM_STATE_ACTIVE)
			goto exit;

		/* First we want to make sure we power off everything
		 * and then activate back again
		 */
		device_for_each_child(arche_pdata->dev, NULL, apb_poweroff);
		arche_platform_poweroff_seq(arche_pdata);

		arche_platform_wd_irq_en(arche_pdata);
		ret = arche_platform_coldboot_seq(arche_pdata);
		if (ret)
			goto exit;

	} else if (sysfs_streq(buf, "standby")) {
		if (arche_pdata->state == ARCHE_PLATFORM_STATE_STANDBY)
			goto exit;

		dev_warn(arche_pdata->dev, "standby state not supported\n");
	} else if (sysfs_streq(buf, "fw_flashing")) {
		if (arche_pdata->state == ARCHE_PLATFORM_STATE_FW_FLASHING)
			goto exit;

		/*
		 * Here we only control SVC.
		 *
		 * In case of FW_FLASHING mode we do not want to control
		 * APBs, as in case of V2, SPI bus is shared between both
		 * the APBs. So let user chose which APB he wants to flash.
		 */
		arche_platform_poweroff_seq(arche_pdata);

		ret = arche_platform_fw_flashing_seq(arche_pdata);
		if (ret)
			goto exit;
	} else {
		dev_err(arche_pdata->dev, "unknown state\n");
		ret = -EINVAL;
	}

exit:
	mutex_unlock(&arche_pdata->platform_state_mutex);
	return ret ? ret : count;
}
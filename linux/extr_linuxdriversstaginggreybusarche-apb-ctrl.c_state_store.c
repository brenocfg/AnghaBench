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
struct platform_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct arche_apb_ctrl_drvdata {scalar_t__ state; int init_disabled; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ ARCHE_PLATFORM_STATE_ACTIVE ; 
 scalar_t__ ARCHE_PLATFORM_STATE_FW_FLASHING ; 
 scalar_t__ ARCHE_PLATFORM_STATE_OFF ; 
 scalar_t__ ARCHE_PLATFORM_STATE_STANDBY ; 
 int EINVAL ; 
 int coldboot_seq (struct platform_device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int fw_flashing_seq (struct platform_device*) ; 
 struct arche_apb_ctrl_drvdata* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  poweroff_seq (struct platform_device*) ; 
 int standby_boot_seq (struct platform_device*) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static ssize_t state_store(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct arche_apb_ctrl_drvdata *apb = platform_get_drvdata(pdev);
	int ret = 0;
	bool is_disabled;

	if (sysfs_streq(buf, "off")) {
		if (apb->state == ARCHE_PLATFORM_STATE_OFF)
			return count;

		poweroff_seq(pdev);
	} else if (sysfs_streq(buf, "active")) {
		if (apb->state == ARCHE_PLATFORM_STATE_ACTIVE)
			return count;

		poweroff_seq(pdev);
		is_disabled = apb->init_disabled;
		apb->init_disabled = false;
		ret = coldboot_seq(pdev);
		if (ret)
			apb->init_disabled = is_disabled;
	} else if (sysfs_streq(buf, "standby")) {
		if (apb->state == ARCHE_PLATFORM_STATE_STANDBY)
			return count;

		ret = standby_boot_seq(pdev);
	} else if (sysfs_streq(buf, "fw_flashing")) {
		if (apb->state == ARCHE_PLATFORM_STATE_FW_FLASHING)
			return count;

		/*
		 * First we want to make sure we power off everything
		 * and then enter FW flashing state
		 */
		poweroff_seq(pdev);
		ret = fw_flashing_seq(pdev);
	} else {
		dev_err(dev, "unknown state\n");
		ret = -EINVAL;
	}

	return ret ? ret : count;
}
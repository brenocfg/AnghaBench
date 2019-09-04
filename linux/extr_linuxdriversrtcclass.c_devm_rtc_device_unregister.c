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
struct rtc_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  devm_rtc_device_match ; 
 int /*<<< orphan*/  devm_rtc_device_release ; 
 int devres_release (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rtc_device*) ; 

void devm_rtc_device_unregister(struct device *dev, struct rtc_device *rtc)
{
	int rc;

	rc = devres_release(dev, devm_rtc_device_release,
				devm_rtc_device_match, rtc);
	WARN_ON(rc);
}
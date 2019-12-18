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

/* Variables and functions */
 scalar_t__ device_property_present (struct device*,char*) ; 

__attribute__((used)) static bool rt5645_check_dp(struct device *dev)
{
	if (device_property_present(dev, "realtek,in2-differential") ||
	    device_property_present(dev, "realtek,dmic1-data-pin") ||
	    device_property_present(dev, "realtek,dmic2-data-pin") ||
	    device_property_present(dev, "realtek,jd-mode"))
		return true;

	return false;
}
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

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 struct platform_device* platform_device_register_simple (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct platform_device *usb_phy_generic_register(void)
{
	return platform_device_register_simple("usb_phy_generic",
			PLATFORM_DEVID_AUTO, NULL, 0);
}
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
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  phy; } ;
struct keystone_usbphy {TYPE_1__ usb_phy_gen; } ;

/* Variables and functions */
 struct keystone_usbphy* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int keystone_usbphy_remove(struct platform_device *pdev)
{
	struct keystone_usbphy *k_phy = platform_get_drvdata(pdev);

	usb_remove_phy(&k_phy->usb_phy_gen.phy);

	return 0;
}
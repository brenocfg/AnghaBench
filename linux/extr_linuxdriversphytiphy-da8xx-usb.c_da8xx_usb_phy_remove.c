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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct da8xx_usb_phy {int /*<<< orphan*/  usb11_phy; int /*<<< orphan*/  usb20_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  phy_remove_lookup (int /*<<< orphan*/ ,char*,char*) ; 
 struct da8xx_usb_phy* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int da8xx_usb_phy_remove(struct platform_device *pdev)
{
	struct da8xx_usb_phy *d_phy = platform_get_drvdata(pdev);

	if (!pdev->dev.of_node) {
		phy_remove_lookup(d_phy->usb20_phy, "usb-phy", "musb-da8xx");
		phy_remove_lookup(d_phy->usb11_phy, "usb-phy", "ohci-da8xx");
	}

	return 0;
}
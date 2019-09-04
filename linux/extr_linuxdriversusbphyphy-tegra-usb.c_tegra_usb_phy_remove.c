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
struct tegra_usb_phy {int /*<<< orphan*/  u_phy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct tegra_usb_phy* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  tegra_usb_phy_close (struct tegra_usb_phy*) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_usb_phy_remove(struct platform_device *pdev)
{
	struct tegra_usb_phy *tegra_phy = platform_get_drvdata(pdev);

	usb_remove_phy(&tegra_phy->u_phy);
	tegra_usb_phy_close(tegra_phy);

	return 0;
}
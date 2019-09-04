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
struct phy_usb_instance {int dummy; } ;
struct phy {int dummy; } ;
struct exynos5_usbdrd_phy {int dummy; } ;

/* Variables and functions */
 int exynos5420_usbdrd_phy_calibrate (struct exynos5_usbdrd_phy*) ; 
 struct phy_usb_instance* phy_get_drvdata (struct phy*) ; 
 struct exynos5_usbdrd_phy* to_usbdrd_phy (struct phy_usb_instance*) ; 

__attribute__((used)) static int exynos5_usbdrd_phy_calibrate(struct phy *phy)
{
	struct phy_usb_instance *inst = phy_get_drvdata(phy);
	struct exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	return exynos5420_usbdrd_phy_calibrate(phy_drd);
}
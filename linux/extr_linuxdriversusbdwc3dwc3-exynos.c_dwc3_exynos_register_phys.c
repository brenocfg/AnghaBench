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
struct usb_phy_generic_platform_data {int gpio_reset; int /*<<< orphan*/  type; } ;
struct platform_device {int dummy; } ;
struct dwc3_exynos {struct platform_device* usb2_phy; struct platform_device* usb3_phy; } ;
typedef  int /*<<< orphan*/  pdata ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PLATFORM_DEVID_AUTO ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB2 ; 
 int /*<<< orphan*/  USB_PHY_TYPE_USB3 ; 
 int /*<<< orphan*/  memset (struct usb_phy_generic_platform_data*,int,int) ; 
 int platform_device_add (struct platform_device*) ; 
 int platform_device_add_data (struct platform_device*,struct usb_phy_generic_platform_data*,int) ; 
 struct platform_device* platform_device_alloc (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_del (struct platform_device*) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static int dwc3_exynos_register_phys(struct dwc3_exynos *exynos)
{
	struct usb_phy_generic_platform_data pdata;
	struct platform_device	*pdev;
	int			ret;

	memset(&pdata, 0x00, sizeof(pdata));

	pdev = platform_device_alloc("usb_phy_generic", PLATFORM_DEVID_AUTO);
	if (!pdev)
		return -ENOMEM;

	exynos->usb2_phy = pdev;
	pdata.type = USB_PHY_TYPE_USB2;
	pdata.gpio_reset = -1;

	ret = platform_device_add_data(exynos->usb2_phy, &pdata, sizeof(pdata));
	if (ret)
		goto err1;

	pdev = platform_device_alloc("usb_phy_generic", PLATFORM_DEVID_AUTO);
	if (!pdev) {
		ret = -ENOMEM;
		goto err1;
	}

	exynos->usb3_phy = pdev;
	pdata.type = USB_PHY_TYPE_USB3;

	ret = platform_device_add_data(exynos->usb3_phy, &pdata, sizeof(pdata));
	if (ret)
		goto err2;

	ret = platform_device_add(exynos->usb2_phy);
	if (ret)
		goto err2;

	ret = platform_device_add(exynos->usb3_phy);
	if (ret)
		goto err3;

	return 0;

err3:
	platform_device_del(exynos->usb2_phy);

err2:
	platform_device_put(exynos->usb3_phy);

err1:
	platform_device_put(exynos->usb2_phy);

	return ret;
}
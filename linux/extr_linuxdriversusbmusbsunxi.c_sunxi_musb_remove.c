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
struct sunxi_glue {int /*<<< orphan*/  musb_pdev; struct platform_device* usb_phy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct sunxi_glue* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_phy_generic_unregister (struct platform_device*) ; 

__attribute__((used)) static int sunxi_musb_remove(struct platform_device *pdev)
{
	struct sunxi_glue *glue = platform_get_drvdata(pdev);
	struct platform_device *usb_phy = glue->usb_phy;

	platform_device_unregister(glue->musb_pdev);
	usb_phy_generic_unregister(usb_phy);

	return 0;
}
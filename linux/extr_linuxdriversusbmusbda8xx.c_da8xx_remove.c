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
struct da8xx_glue {int /*<<< orphan*/  usb_phy; int /*<<< orphan*/  musb; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 struct da8xx_glue* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_phy_generic_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da8xx_remove(struct platform_device *pdev)
{
	struct da8xx_glue		*glue = platform_get_drvdata(pdev);

	platform_device_unregister(glue->musb);
	usb_phy_generic_unregister(glue->usb_phy);

	return 0;
}
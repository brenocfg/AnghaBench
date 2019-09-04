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
struct usb_phy_generic {int /*<<< orphan*/  phy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct usb_phy_generic* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_remove_phy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int usb_phy_generic_remove(struct platform_device *pdev)
{
	struct usb_phy_generic *nop = platform_get_drvdata(pdev);

	usb_remove_phy(&nop->phy);

	return 0;
}
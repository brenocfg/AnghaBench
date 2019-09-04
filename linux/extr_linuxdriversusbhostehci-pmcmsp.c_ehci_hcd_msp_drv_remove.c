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
struct usb_hcd {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSP_PIN_USB0_HOST_DEV ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 struct usb_hcd* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  usb_hcd_msp_remove (struct usb_hcd*,struct platform_device*) ; 

__attribute__((used)) static int ehci_hcd_msp_drv_remove(struct platform_device *pdev)
{
	struct usb_hcd *hcd = platform_get_drvdata(pdev);

	usb_hcd_msp_remove(hcd, pdev);

	/* free TWI GPIO USB_HOST_DEV pin */
	gpio_free(MSP_PIN_USB0_HOST_DEV);

	return 0;
}
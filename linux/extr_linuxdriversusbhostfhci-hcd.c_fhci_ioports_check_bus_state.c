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
typedef  int u8 ;
struct fhci_hcd {int /*<<< orphan*/ * gpios; } ;

/* Variables and functions */
 size_t GPIO_USBOE ; 
 size_t GPIO_USBRN ; 
 size_t GPIO_USBRP ; 
 scalar_t__ gpio_get_value (int /*<<< orphan*/ ) ; 

int fhci_ioports_check_bus_state(struct fhci_hcd *fhci)
{
	u8 bits = 0;

	/* check USBOE,if transmitting,exit */
	if (!gpio_get_value(fhci->gpios[GPIO_USBOE]))
		return -1;

	/* check USBRP */
	if (gpio_get_value(fhci->gpios[GPIO_USBRP]))
		bits |= 0x2;

	/* check USBRN */
	if (gpio_get_value(fhci->gpios[GPIO_USBRN]))
		bits |= 0x1;

	return bits;
}
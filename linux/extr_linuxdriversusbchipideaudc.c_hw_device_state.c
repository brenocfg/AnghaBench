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
typedef  int u32 ;
struct ci_hdrc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ENDPTLISTADDR ; 
 int /*<<< orphan*/  OP_USBINTR ; 
 int USBi_PCI ; 
 int USBi_SLI ; 
 int USBi_UEI ; 
 int USBi_UI ; 
 int USBi_URI ; 
 int /*<<< orphan*/  hw_write (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int hw_device_state(struct ci_hdrc *ci, u32 dma)
{
	if (dma) {
		hw_write(ci, OP_ENDPTLISTADDR, ~0, dma);
		/* interrupt, error, port change, reset, sleep/suspend */
		hw_write(ci, OP_USBINTR, ~0,
			     USBi_UI|USBi_UEI|USBi_PCI|USBi_URI|USBi_SLI);
	} else {
		hw_write(ci, OP_USBINTR, ~0, 0);
	}
	return 0;
}
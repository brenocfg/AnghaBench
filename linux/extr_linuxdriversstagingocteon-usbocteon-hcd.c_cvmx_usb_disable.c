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
struct octeon_hcd {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_USBCX_HPRT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_SET_FIELD32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cvmx_usbcx_hprt ; 
 int /*<<< orphan*/  prtena ; 

__attribute__((used)) static int cvmx_usb_disable(struct octeon_hcd *usb)
{
	/* Disable the port */
	USB_SET_FIELD32(CVMX_USBCX_HPRT(usb->index), cvmx_usbcx_hprt,
			prtena, 1);
	return 0;
}
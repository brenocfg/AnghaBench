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
struct usbhsh_hpriv {int dummy; } ;
struct usb_hcd {int dummy; } ;

/* Variables and functions */
 struct usbhsh_hpriv* usbhsh_hcd_to_hpriv (struct usb_hcd*) ; 
 int usbhsh_port_stat_get (struct usbhsh_hpriv*) ; 

__attribute__((used)) static int usbhsh_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	struct usbhsh_hpriv *hpriv = usbhsh_hcd_to_hpriv(hcd);
	int roothub_id = 1; /* only 1 root hub */

	/*
	 * does port stat was changed ?
	 * check USB_PORT_STAT_C_xxx << 16
	 */
	if (usbhsh_port_stat_get(hpriv) & 0xFFFF0000)
		*buf = (1 << roothub_id);
	else
		*buf = 0;

	return !!(*buf);
}
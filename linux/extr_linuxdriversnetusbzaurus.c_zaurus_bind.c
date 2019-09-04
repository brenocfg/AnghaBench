#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usbnet {TYPE_1__* net; scalar_t__ rx_urb_size; } ;
struct usb_interface {int dummy; } ;
struct TYPE_2__ {scalar_t__ mtu; scalar_t__ hard_header_len; } ;

/* Variables and functions */
 int usbnet_generic_cdc_bind (struct usbnet*,struct usb_interface*) ; 

__attribute__((used)) static int zaurus_bind(struct usbnet *dev, struct usb_interface *intf)
{
	/* Belcarra's funky framing has other options; mostly
	 * TRAILERS (!) with 4 bytes CRC, and maybe 2 pad bytes.
	 */
	dev->net->hard_header_len += 6;
	dev->rx_urb_size = dev->net->hard_header_len + dev->net->mtu;
	return usbnet_generic_cdc_bind(dev, intf);
}
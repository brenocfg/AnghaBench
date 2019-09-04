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
struct usbnet {int /*<<< orphan*/  net; } ;
struct urb {int actual_length; unsigned char* transfer_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_LINK_RESET ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbnet_defer_kevent (struct usbnet*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ch9200_status(struct usbnet *dev, struct urb *urb)
{
	int link;
	unsigned char *buf;

	if (urb->actual_length < 16)
		return;

	buf = urb->transfer_buffer;
	link = !!(buf[0] & 0x01);

	if (link) {
		netif_carrier_on(dev->net);
		usbnet_defer_kevent(dev, EVENT_LINK_RESET);
	} else {
		netif_carrier_off(dev->net);
	}
}
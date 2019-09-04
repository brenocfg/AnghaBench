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
struct usbnet {int rx_qlen; int rx_urb_size; int tx_qlen; int hard_mtu; TYPE_1__* udev; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
struct TYPE_2__ {int speed; } ;

/* Variables and functions */
 int MAX_QUEUE_MEMORY ; 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_SUPER 129 
#define  USB_SPEED_SUPER_PLUS 128 

void usbnet_update_max_qlen(struct usbnet *dev)
{
	enum usb_device_speed speed = dev->udev->speed;

	switch (speed) {
	case USB_SPEED_HIGH:
		dev->rx_qlen = MAX_QUEUE_MEMORY / dev->rx_urb_size;
		dev->tx_qlen = MAX_QUEUE_MEMORY / dev->hard_mtu;
		break;
	case USB_SPEED_SUPER:
	case USB_SPEED_SUPER_PLUS:
		/*
		 * Not take default 5ms qlen for super speed HC to
		 * save memory, and iperf tests show 2.5ms qlen can
		 * work well
		 */
		dev->rx_qlen = 5 * MAX_QUEUE_MEMORY / dev->rx_urb_size;
		dev->tx_qlen = 5 * MAX_QUEUE_MEMORY / dev->hard_mtu;
		break;
	default:
		dev->rx_qlen = dev->tx_qlen = 4;
	}
}
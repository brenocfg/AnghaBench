#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usbnet {TYPE_2__* driver_info; int /*<<< orphan*/  udev; int /*<<< orphan*/  out; int /*<<< orphan*/  in; TYPE_1__* net; int /*<<< orphan*/  hard_mtu; } ;
struct usb_interface {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;
struct TYPE_3__ {int hard_header_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_RCV_BUF_SIZE ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int genelink_bind(struct usbnet *dev, struct usb_interface *intf)
{
	dev->hard_mtu = GL_RCV_BUF_SIZE;
	dev->net->hard_header_len += 4;
	dev->in = usb_rcvbulkpipe(dev->udev, dev->driver_info->in);
	dev->out = usb_sndbulkpipe(dev->udev, dev->driver_info->out);
	return 0;
}
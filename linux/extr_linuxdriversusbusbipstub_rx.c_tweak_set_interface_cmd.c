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
struct usb_ctrlrequest {int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
struct urb {TYPE_1__* dev; scalar_t__ setup_packet; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_set_interface (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbip_dbg_stub_rx (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tweak_set_interface_cmd(struct urb *urb)
{
	struct usb_ctrlrequest *req;
	__u16 alternate;
	__u16 interface;
	int ret;

	req = (struct usb_ctrlrequest *) urb->setup_packet;
	alternate = le16_to_cpu(req->wValue);
	interface = le16_to_cpu(req->wIndex);

	usbip_dbg_stub_rx("set_interface: inf %u alt %u\n",
			  interface, alternate);

	ret = usb_set_interface(urb->dev, interface, alternate);
	if (ret < 0)
		dev_err(&urb->dev->dev,
			"usb_set_interface error: inf %u alt %u ret %d\n",
			interface, alternate, ret);
	else
		dev_info(&urb->dev->dev,
			"usb_set_interface done: inf %u alt %u\n",
			interface, alternate);

	return ret;
}
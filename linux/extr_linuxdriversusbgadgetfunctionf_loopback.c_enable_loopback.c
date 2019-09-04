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
struct usb_composite_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct f_loopback {int /*<<< orphan*/  in_ep; int /*<<< orphan*/  out_ep; TYPE_1__ function; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct usb_composite_dev*,char*,int /*<<< orphan*/ ) ; 
 int alloc_requests (struct usb_composite_dev*,struct f_loopback*) ; 
 int enable_endpoint (struct usb_composite_dev*,struct f_loopback*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_ep_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enable_loopback(struct usb_composite_dev *cdev, struct f_loopback *loop)
{
	int					result = 0;

	result = enable_endpoint(cdev, loop, loop->in_ep);
	if (result)
		goto out;

	result = enable_endpoint(cdev, loop, loop->out_ep);
	if (result)
		goto disable_in;

	result = alloc_requests(cdev, loop);
	if (result)
		goto disable_out;

	DBG(cdev, "%s enabled\n", loop->function.name);
	return 0;

disable_out:
	usb_ep_disable(loop->out_ep);
disable_in:
	usb_ep_disable(loop->in_ep);
out:
	return result;
}
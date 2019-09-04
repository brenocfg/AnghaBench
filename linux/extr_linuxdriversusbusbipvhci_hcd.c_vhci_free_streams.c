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
struct usb_host_endpoint {int dummy; } ;
struct TYPE_4__ {TYPE_1__* root_hub; } ;
struct usb_hcd {TYPE_2__ self; } ;
struct usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int vhci_free_streams(struct usb_hcd *hcd, struct usb_device *udev,
	struct usb_host_endpoint **eps, unsigned int num_eps,
	gfp_t mem_flags)
{
	dev_dbg(&hcd->self.root_hub->dev, "vhci_free_streams not implemented\n");
	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int /*<<< orphan*/  state; } ;
struct fhci_hcd {TYPE_3__* vroot_hub; int /*<<< orphan*/  lock; int /*<<< orphan*/  usb_lld; } ;
struct TYPE_5__ {scalar_t__ wPortChange; scalar_t__ wPortStatus; } ;
struct TYPE_4__ {scalar_t__ wHubChange; scalar_t__ wHubStatus; } ;
struct TYPE_6__ {int dev_num; TYPE_2__ port; TYPE_1__ hub; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HC_STATE_RUNNING ; 
 int /*<<< orphan*/  fhci_create_lld (struct fhci_hcd*) ; 
 int /*<<< orphan*/  fhci_err (struct fhci_hcd*,char*) ; 
 int /*<<< orphan*/  fhci_mem_free (struct fhci_hcd*) ; 
 int fhci_mem_init (struct fhci_hcd*) ; 
 int /*<<< orphan*/  fhci_usb_enable (struct fhci_hcd*) ; 
 int fhci_usb_init (struct fhci_hcd*) ; 
 struct fhci_hcd* hcd_to_fhci (struct usb_hcd*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fhci_start(struct usb_hcd *hcd)
{
	int ret;
	struct fhci_hcd *fhci = hcd_to_fhci(hcd);

	ret = fhci_mem_init(fhci);
	if (ret) {
		fhci_err(fhci, "failed to allocate memory\n");
		goto err;
	}

	fhci->usb_lld = fhci_create_lld(fhci);
	if (!fhci->usb_lld) {
		fhci_err(fhci, "low level driver config failed\n");
		ret = -ENOMEM;
		goto err;
	}

	ret = fhci_usb_init(fhci);
	if (ret) {
		fhci_err(fhci, "low level driver initialize failed\n");
		goto err;
	}

	spin_lock_init(&fhci->lock);

	/* connect the virtual root hub */
	fhci->vroot_hub->dev_num = 1;	/* this field may be needed to fix */
	fhci->vroot_hub->hub.wHubStatus = 0;
	fhci->vroot_hub->hub.wHubChange = 0;
	fhci->vroot_hub->port.wPortStatus = 0;
	fhci->vroot_hub->port.wPortChange = 0;

	hcd->state = HC_STATE_RUNNING;

	/*
	 * From here on, hub_wq concurrently accesses the root
	 * hub; drivers will be talking to enumerated devices.
	 * (On restart paths, hub_wq already knows about the root
	 * hub and could find work as soon as we wrote FLAG_CF.)
	 *
	 * Before this point the HC was idle/ready.  After, hub_wq
	 * and device drivers may start it running.
	 */
	fhci_usb_enable(fhci);
	return 0;
err:
	fhci_mem_free(fhci);
	return ret;
}
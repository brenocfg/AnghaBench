#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct urb {int /*<<< orphan*/  unlinked; int /*<<< orphan*/  pipe; } ;
struct TYPE_7__ {int /*<<< orphan*/  complete; int /*<<< orphan*/  unlink; } ;
struct ehci_hcd {TYPE_2__ stats; } ;
struct TYPE_6__ {int /*<<< orphan*/  bandwidth_int_reqs; } ;
struct TYPE_8__ {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNT (int /*<<< orphan*/ ) ; 
 int EINPROGRESS ; 
 int EREMOTEIO ; 
 scalar_t__ PIPE_INTERRUPT ; 
 TYPE_3__* ehci_to_hcd (struct ehci_hcd*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (TYPE_3__*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb_from_ep (TYPE_3__*,struct urb*) ; 
 scalar_t__ usb_pipetype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ehci_urb_done(struct ehci_hcd *ehci, struct urb *urb, int status)
{
	if (usb_pipetype(urb->pipe) == PIPE_INTERRUPT) {
		/* ... update hc-wide periodic stats */
		ehci_to_hcd(ehci)->self.bandwidth_int_reqs--;
	}

	if (unlikely(urb->unlinked)) {
		COUNT(ehci->stats.unlink);
	} else {
		/* report non-error and short read status as zero */
		if (status == -EINPROGRESS || status == -EREMOTEIO)
			status = 0;
		COUNT(ehci->stats.complete);
	}

#ifdef EHCI_URB_TRACE
	ehci_dbg (ehci,
		"%s %s urb %p ep%d%s status %d len %d/%d\n",
		__func__, urb->dev->devpath, urb,
		usb_pipeendpoint (urb->pipe),
		usb_pipein (urb->pipe) ? "in" : "out",
		status,
		urb->actual_length, urb->transfer_buffer_length);
#endif

	usb_hcd_unlink_urb_from_ep(ehci_to_hcd(ehci), urb);
	usb_hcd_giveback_urb(ehci_to_hcd(ehci), urb, status);
}
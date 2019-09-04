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
struct seq_file {struct dwc3_ep* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc; } ;
struct dwc3_ep {int flags; TYPE_1__ endpoint; struct dwc3* dwc; } ;
struct dwc3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int DWC3_EP_ENABLED ; 
#define  USB_ENDPOINT_XFER_BULK 131 
#define  USB_ENDPOINT_XFER_CONTROL 130 
#define  USB_ENDPOINT_XFER_INT 129 
#define  USB_ENDPOINT_XFER_ISOC 128 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_endpoint_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwc3_transfer_type_show(struct seq_file *s, void *unused)
{
	struct dwc3_ep		*dep = s->private;
	struct dwc3		*dwc = dep->dwc;
	unsigned long		flags;

	spin_lock_irqsave(&dwc->lock, flags);
	if (!(dep->flags & DWC3_EP_ENABLED) ||
			!dep->endpoint.desc) {
		seq_printf(s, "--\n");
		goto out;
	}

	switch (usb_endpoint_type(dep->endpoint.desc)) {
	case USB_ENDPOINT_XFER_CONTROL:
		seq_printf(s, "control\n");
		break;
	case USB_ENDPOINT_XFER_ISOC:
		seq_printf(s, "isochronous\n");
		break;
	case USB_ENDPOINT_XFER_BULK:
		seq_printf(s, "bulk\n");
		break;
	case USB_ENDPOINT_XFER_INT:
		seq_printf(s, "interrupt\n");
		break;
	default:
		seq_printf(s, "--\n");
	}

out:
	spin_unlock_irqrestore(&dwc->lock, flags);

	return 0;
}
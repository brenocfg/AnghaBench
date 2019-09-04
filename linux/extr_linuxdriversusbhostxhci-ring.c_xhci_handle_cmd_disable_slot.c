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
struct xhci_virt_device {int /*<<< orphan*/  out_ctx; } ;
struct xhci_slot_ctx {int dummy; } ;
struct xhci_hcd {int quirks; struct xhci_virt_device** devs; } ;

/* Variables and functions */
 int XHCI_EP_LIMIT_QUIRK ; 
 int /*<<< orphan*/  trace_xhci_handle_cmd_disable_slot (struct xhci_slot_ctx*) ; 
 int /*<<< orphan*/  xhci_free_device_endpoint_resources (struct xhci_hcd*,struct xhci_virt_device*,int) ; 
 int /*<<< orphan*/  xhci_free_virt_device (struct xhci_hcd*,int) ; 
 struct xhci_slot_ctx* xhci_get_slot_ctx (struct xhci_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xhci_handle_cmd_disable_slot(struct xhci_hcd *xhci, int slot_id)
{
	struct xhci_virt_device *virt_dev;
	struct xhci_slot_ctx *slot_ctx;

	virt_dev = xhci->devs[slot_id];
	if (!virt_dev)
		return;

	slot_ctx = xhci_get_slot_ctx(xhci, virt_dev->out_ctx);
	trace_xhci_handle_cmd_disable_slot(slot_ctx);

	if (xhci->quirks & XHCI_EP_LIMIT_QUIRK)
		/* Delete default control endpoint resources */
		xhci_free_device_endpoint_resources(xhci, virt_dev, true);
	xhci_free_virt_device(xhci, slot_id);
}
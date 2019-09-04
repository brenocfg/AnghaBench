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
struct xhci_hcd {int quirks; } ;
struct xhci_event_cmd {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEC_FW_MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEC_FW_MINOR (int /*<<< orphan*/ ) ; 
 int XHCI_NEC_HOST ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xhci_dbg_quirks ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_warn (struct xhci_hcd*,char*) ; 

__attribute__((used)) static void xhci_handle_cmd_nec_get_fw(struct xhci_hcd *xhci,
		struct xhci_event_cmd *event)
{
	if (!(xhci->quirks & XHCI_NEC_HOST)) {
		xhci_warn(xhci, "WARN NEC_GET_FW command on non-NEC host\n");
		return;
	}
	xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
			"NEC firmware version %2x.%02x",
			NEC_FW_MAJOR(le32_to_cpu(event->status)),
			NEC_FW_MINOR(le32_to_cpu(event->status)));
}
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
typedef  scalar_t__ u32 ;
struct xhci_input_control_ctx {int dummy; } ;
struct xhci_hcd {scalar_t__ num_active_eps; scalar_t__ limit_active_eps; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  trace_xhci_dbg_quirks ; 
 scalar_t__ xhci_count_num_new_endpoints (struct xhci_hcd*,struct xhci_input_control_ctx*) ; 
 int /*<<< orphan*/  xhci_dbg_trace (struct xhci_hcd*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static int xhci_reserve_host_resources(struct xhci_hcd *xhci,
		struct xhci_input_control_ctx *ctrl_ctx)
{
	u32 added_eps;

	added_eps = xhci_count_num_new_endpoints(xhci, ctrl_ctx);
	if (xhci->num_active_eps + added_eps > xhci->limit_active_eps) {
		xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
				"Not enough ep ctxs: "
				"%u active, need to add %u, limit is %u.",
				xhci->num_active_eps, added_eps,
				xhci->limit_active_eps);
		return -ENOMEM;
	}
	xhci->num_active_eps += added_eps;
	xhci_dbg_trace(xhci, trace_xhci_dbg_quirks,
			"Adding %u ep ctxs, %u now active.", added_eps,
			xhci->num_active_eps);
	return 0;
}
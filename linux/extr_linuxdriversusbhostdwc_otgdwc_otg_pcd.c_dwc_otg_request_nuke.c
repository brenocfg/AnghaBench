#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dwc_otg_pcd_request_t ;
struct TYPE_4__ {int stopped; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ dwc_otg_pcd_ep_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_CIRCLEQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DWC_CIRCLEQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_E_SHUTDOWN ; 
 int /*<<< orphan*/  dwc_otg_request_done (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dwc_otg_request_nuke(dwc_otg_pcd_ep_t * ep)
{
	dwc_otg_pcd_request_t *req;

	ep->stopped = 1;

	/* called with irqs blocked?? */
	while (!DWC_CIRCLEQ_EMPTY(&ep->queue)) {
		req = DWC_CIRCLEQ_FIRST(&ep->queue);
		dwc_otg_request_done(ep, req, -DWC_E_SHUTDOWN);
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  qh_list_entry; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ASSERT (TYPE_1__*,char*) ; 
 scalar_t__ DWC_LIST_EMPTY (int /*<<< orphan*/ *) ; 

int dwc_otg_hcd_is_bandwidth_freed(dwc_otg_hcd_t * hcd, void *ep_handle)
{
	dwc_otg_qh_t *qh = (dwc_otg_qh_t *) ep_handle;
	int freed = 0;
	DWC_ASSERT(qh, "qh is not allocated\n");

	if (DWC_LIST_EMPTY(&qh->qh_list_entry)) {
		freed = 1;
	}

	return freed;
}
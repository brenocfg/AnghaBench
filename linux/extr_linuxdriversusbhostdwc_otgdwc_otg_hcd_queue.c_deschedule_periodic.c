#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* frame_usecs; scalar_t__ usecs; int /*<<< orphan*/  qh_list_entry; } ;
typedef  TYPE_1__ dwc_otg_qh_t ;
struct TYPE_6__ {int /*<<< orphan*/ * frame_usecs; int /*<<< orphan*/  periodic_channels; int /*<<< orphan*/  periodic_usecs; } ;
typedef  TYPE_2__ dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_LIST_REMOVE_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  microframe_schedule ; 

__attribute__((used)) static void deschedule_periodic(dwc_otg_hcd_t * hcd, dwc_otg_qh_t * qh)
{
	int i;
	DWC_LIST_REMOVE_INIT(&qh->qh_list_entry);

	/* Update claimed usecs per (micro)frame. */
	hcd->periodic_usecs -= qh->usecs;

	if (!microframe_schedule) {
		/* Release the periodic channel reservation. */
		hcd->periodic_channels--;
	} else {
		for (i = 0; i < 8; i++) {
			hcd->frame_usecs[i] += qh->frame_usecs[i];
			qh->frame_usecs[i] = 0;
		}
	}
}
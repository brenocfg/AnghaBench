#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* qh; int /*<<< orphan*/ * urb; } ;
typedef  TYPE_2__ dwc_otg_qtd_t ;
struct TYPE_15__ {int /*<<< orphan*/  qtd_list; } ;
typedef  TYPE_3__ dwc_otg_qh_t ;
typedef  int /*<<< orphan*/  dwc_otg_hcd_urb_t ;
struct TYPE_16__ {TYPE_1__* fiq_state; } ;
typedef  TYPE_4__ dwc_otg_hcd_t ;
struct TYPE_13__ {int kick_np_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_CIRCLEQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int DWC_E_NO_MEMORY ; 
 int dwc_otg_hcd_qh_add (TYPE_4__*,TYPE_3__*) ; 
 TYPE_3__* dwc_otg_hcd_qh_create (TYPE_4__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ fiq_enable ; 
 int /*<<< orphan*/  qtd_list_entry ; 

int dwc_otg_hcd_qtd_add(dwc_otg_qtd_t * qtd,
			dwc_otg_hcd_t * hcd, dwc_otg_qh_t ** qh, int atomic_alloc)
{
	int retval = 0;
	dwc_otg_hcd_urb_t *urb = qtd->urb;

	/*
	 * Get the QH which holds the QTD-list to insert to. Create QH if it
	 * doesn't exist.
	 */
	if (*qh == NULL) {
		*qh = dwc_otg_hcd_qh_create(hcd, urb, atomic_alloc);
		if (*qh == NULL) {
			retval = -DWC_E_NO_MEMORY;
			goto done;
		} else {
			if (fiq_enable)
				hcd->fiq_state->kick_np_queues = 1;
		}
	}
	retval = dwc_otg_hcd_qh_add(hcd, *qh);
	if (retval == 0) {
		DWC_CIRCLEQ_INSERT_TAIL(&((*qh)->qtd_list), qtd,
					qtd_list_entry);
		qtd->qh = *qh;
	}
done:

	return retval;
}
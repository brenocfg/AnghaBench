#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_1__ ;
typedef  struct TYPE_36__   TYPE_17__ ;
typedef  struct TYPE_35__   TYPE_16__ ;
typedef  struct TYPE_34__   TYPE_15__ ;
typedef  struct TYPE_33__   TYPE_14__ ;
typedef  struct TYPE_32__   TYPE_13__ ;
typedef  struct TYPE_31__   TYPE_12__ ;
typedef  struct TYPE_30__   TYPE_11__ ;
typedef  struct TYPE_29__   TYPE_10__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_43__ {scalar_t__ prtspd; } ;
struct TYPE_31__ {TYPE_7__ b; void* d32; } ;
typedef  TYPE_12__ hprt0_data_t ;
struct TYPE_29__ {int /*<<< orphan*/  sofintr; } ;
struct TYPE_32__ {TYPE_10__ b; void* d32; } ;
typedef  TYPE_13__ gintmsk_data_t ;
typedef  scalar_t__ dwc_otg_transaction_type_e ;
struct TYPE_33__ {TYPE_11__* urb; } ;
typedef  TYPE_14__ dwc_otg_qtd_t ;
struct TYPE_34__ {scalar_t__ ep_type; } ;
typedef  TYPE_15__ dwc_otg_qh_t ;
struct TYPE_35__ {int /*<<< orphan*/  priv; } ;
typedef  TYPE_16__ dwc_otg_hcd_urb_t ;
struct TYPE_37__ {int /*<<< orphan*/  port_connect_status; } ;
struct TYPE_38__ {TYPE_1__ b; } ;
struct TYPE_36__ {TYPE_9__* core_if; TYPE_3__* fops; TYPE_2__ flags; } ;
typedef  TYPE_17__ dwc_otg_hcd_t ;
struct TYPE_40__ {int fs_phy_type; int hs_phy_type; } ;
struct TYPE_41__ {TYPE_4__ b; } ;
struct TYPE_45__ {TYPE_8__* core_global_regs; TYPE_6__* host_if; TYPE_5__ hwcfg2; } ;
struct TYPE_44__ {int /*<<< orphan*/  gintmsk; } ;
struct TYPE_42__ {int /*<<< orphan*/ * hprt0; } ;
struct TYPE_39__ {scalar_t__ (* speed ) (TYPE_17__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_30__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ERROR (char*,...) ; 
 int DWC_E_NO_DEVICE ; 
 int DWC_E_NO_MEMORY ; 
 scalar_t__ DWC_HPRT0_PRTSPD_FULL_SPEED ; 
 scalar_t__ DWC_OTG_TRANSACTION_NONE ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 scalar_t__ UE_BULK ; 
 int URB_GIVEBACK_ASAP ; 
 scalar_t__ USB_SPEED_LOW ; 
 int dwc_otg_hcd_qtd_add (TYPE_14__*,TYPE_17__*,TYPE_15__**,int) ; 
 TYPE_14__* dwc_otg_hcd_qtd_create (TYPE_16__*,int) ; 
 int /*<<< orphan*/  dwc_otg_hcd_qtd_free (TYPE_14__*) ; 
 int /*<<< orphan*/  dwc_otg_hcd_queue_transactions (TYPE_17__*,scalar_t__) ; 
 scalar_t__ dwc_otg_hcd_select_transactions (TYPE_17__*) ; 
 scalar_t__ fiq_enable ; 
 scalar_t__ stub1 (TYPE_17__*,int /*<<< orphan*/ ) ; 

int dwc_otg_hcd_urb_enqueue(dwc_otg_hcd_t * hcd,
			    dwc_otg_hcd_urb_t * dwc_otg_urb, void **ep_handle,
			    int atomic_alloc)
{
	int retval = 0;
	uint8_t needs_scheduling = 0;
	dwc_otg_transaction_type_e tr_type;
	dwc_otg_qtd_t *qtd;
	gintmsk_data_t intr_mask = {.d32 = 0 };
	hprt0_data_t hprt0 = { .d32 = 0 };

#ifdef DEBUG /* integrity checks (Broadcom) */
	if (NULL == hcd->core_if) {
		DWC_ERROR("**** DWC OTG HCD URB Enqueue - HCD has NULL core_if\n");
		/* No longer connected. */
		return -DWC_E_INVALID;
	}
#endif
	if (!hcd->flags.b.port_connect_status) {
		/* No longer connected. */
		DWC_ERROR("Not connected\n");
		return -DWC_E_NO_DEVICE;
	}

	/* Some core configurations cannot support LS traffic on a FS root port */
	if ((hcd->fops->speed(hcd, dwc_otg_urb->priv) == USB_SPEED_LOW) &&
		(hcd->core_if->hwcfg2.b.fs_phy_type == 1) &&
		(hcd->core_if->hwcfg2.b.hs_phy_type == 1)) {
			hprt0.d32 = DWC_READ_REG32(hcd->core_if->host_if->hprt0);
			if (hprt0.b.prtspd == DWC_HPRT0_PRTSPD_FULL_SPEED) {
				return -DWC_E_NO_DEVICE;
			}
	}

	qtd = dwc_otg_hcd_qtd_create(dwc_otg_urb, atomic_alloc);
	if (qtd == NULL) {
		DWC_ERROR("DWC OTG HCD URB Enqueue failed creating QTD\n");
		return -DWC_E_NO_MEMORY;
	}
#ifdef DEBUG /* integrity checks (Broadcom) */
	if (qtd->urb == NULL) {
		DWC_ERROR("**** DWC OTG HCD URB Enqueue created QTD with no URBs\n");
		return -DWC_E_NO_MEMORY;
	}
	if (qtd->urb->priv == NULL) {
		DWC_ERROR("**** DWC OTG HCD URB Enqueue created QTD URB with no URB handle\n");
		return -DWC_E_NO_MEMORY;
	}
#endif
	intr_mask.d32 = DWC_READ_REG32(&hcd->core_if->core_global_regs->gintmsk);
	if(!intr_mask.b.sofintr || fiq_enable) needs_scheduling = 1;
	if((((dwc_otg_qh_t *)ep_handle)->ep_type == UE_BULK) && !(qtd->urb->flags & URB_GIVEBACK_ASAP))
		/* Do not schedule SG transactions until qtd has URB_GIVEBACK_ASAP set */
		needs_scheduling = 0;

	retval = dwc_otg_hcd_qtd_add(qtd, hcd, (dwc_otg_qh_t **) ep_handle, atomic_alloc);
            // creates a new queue in ep_handle if it doesn't exist already
	if (retval < 0) {
		DWC_ERROR("DWC OTG HCD URB Enqueue failed adding QTD. "
			  "Error status %d\n", retval);
		dwc_otg_hcd_qtd_free(qtd);
		return retval;
	}

	if(needs_scheduling) {
		tr_type = dwc_otg_hcd_select_transactions(hcd);
		if (tr_type != DWC_OTG_TRANSACTION_NONE) {
			dwc_otg_hcd_queue_transactions(hcd, tr_type);
		}
	}
	return retval;
}
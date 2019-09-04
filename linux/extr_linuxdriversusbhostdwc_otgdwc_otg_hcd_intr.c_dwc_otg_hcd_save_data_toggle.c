#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ pid; } ;
struct TYPE_11__ {TYPE_1__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_2__ hctsiz_data_t ;
struct TYPE_12__ {void* data_toggle; } ;
typedef  TYPE_3__ dwc_otg_qtd_t ;
struct TYPE_13__ {void* data_toggle; } ;
typedef  TYPE_4__ dwc_otg_qh_t ;
struct TYPE_14__ {int /*<<< orphan*/  hctsiz; } ;
typedef  TYPE_5__ dwc_otg_hc_regs_t ;
struct TYPE_15__ {scalar_t__ ep_type; TYPE_4__* qh; } ;
typedef  TYPE_6__ dwc_hc_t ;

/* Variables and functions */
 scalar_t__ DWC_HCTSIZ_DATA0 ; 
 scalar_t__ DWC_OTG_EP_TYPE_CONTROL ; 
 void* DWC_OTG_HC_PID_DATA0 ; 
 void* DWC_OTG_HC_PID_DATA1 ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 

void dwc_otg_hcd_save_data_toggle(dwc_hc_t * hc,
			     dwc_otg_hc_regs_t * hc_regs, dwc_otg_qtd_t * qtd)
{
	hctsiz_data_t hctsiz;
	hctsiz.d32 = DWC_READ_REG32(&hc_regs->hctsiz);

	if (hc->ep_type != DWC_OTG_EP_TYPE_CONTROL) {
		dwc_otg_qh_t *qh = hc->qh;
		if (hctsiz.b.pid == DWC_HCTSIZ_DATA0) {
			qh->data_toggle = DWC_OTG_HC_PID_DATA0;
		} else {
			qh->data_toggle = DWC_OTG_HC_PID_DATA1;
		}
	} else {
		if (hctsiz.b.pid == DWC_HCTSIZ_DATA0) {
			qtd->data_toggle = DWC_OTG_HC_PID_DATA0;
		} else {
			qtd->data_toggle = DWC_OTG_HC_PID_DATA1;
		}
	}
}
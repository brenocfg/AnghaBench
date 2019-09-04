#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ in_process; scalar_t__ isoc_split_offset; int /*<<< orphan*/  isoc_split_pos; scalar_t__ complete_split; int /*<<< orphan*/  control_phase; int /*<<< orphan*/  data_toggle; TYPE_2__* urb; } ;
typedef  TYPE_1__ dwc_otg_qtd_t ;
struct TYPE_7__ {TYPE_1__* qtd; int /*<<< orphan*/  pipe_info; } ;
typedef  TYPE_2__ dwc_otg_hcd_urb_t ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_HCSPLIT_XACTPOS_ALL ; 
 int /*<<< orphan*/  DWC_OTG_CONTROL_SETUP ; 
 int /*<<< orphan*/  DWC_OTG_HC_PID_DATA1 ; 
 scalar_t__ UE_CONTROL ; 
 int /*<<< orphan*/  dwc_memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dwc_otg_hcd_get_pipe_type (int /*<<< orphan*/ *) ; 

void dwc_otg_hcd_qtd_init(dwc_otg_qtd_t * qtd, dwc_otg_hcd_urb_t * urb)
{
	dwc_memset(qtd, 0, sizeof(dwc_otg_qtd_t));
	qtd->urb = urb;
	if (dwc_otg_hcd_get_pipe_type(&urb->pipe_info) == UE_CONTROL) {
		/*
		 * The only time the QTD data toggle is used is on the data
		 * phase of control transfers. This phase always starts with
		 * DATA1.
		 */
		qtd->data_toggle = DWC_OTG_HC_PID_DATA1;
		qtd->control_phase = DWC_OTG_CONTROL_SETUP;
	}

	/* start split */
	qtd->complete_split = 0;
	qtd->isoc_split_pos = DWC_HCSPLIT_XACTPOS_ALL;
	qtd->isoc_split_offset = 0;
	qtd->in_process = 0;

	/* Store the qtd ptr in the urb to reference what QTD. */
	urb->qtd = qtd;
	return;
}
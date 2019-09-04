#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_9__ {size_t chnum; size_t bcnt; size_t pktsts; int /*<<< orphan*/  dpid; } ;
struct TYPE_10__ {TYPE_2__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_3__ host_grxsts_data_t ;
struct TYPE_11__ {TYPE_6__* core_if; TYPE_5__** hc_ptr_array; } ;
typedef  TYPE_4__ dwc_otg_hcd_t ;
struct TYPE_12__ {size_t xfer_buff; size_t xfer_count; int /*<<< orphan*/  data_pid_start; } ;
typedef  TYPE_5__ dwc_hc_t ;
struct TYPE_13__ {TYPE_1__* core_global_regs; } ;
struct TYPE_8__ {int /*<<< orphan*/  grxstsp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HCD ; 
 int /*<<< orphan*/  DBG_HCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DWC_ERROR (char*,...) ; 
#define  DWC_GRXSTS_PKTSTS_CH_HALTED 131 
#define  DWC_GRXSTS_PKTSTS_DATA_TOGGLE_ERR 130 
#define  DWC_GRXSTS_PKTSTS_IN 129 
#define  DWC_GRXSTS_PKTSTS_IN_XFER_COMP 128 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_read_packet (TYPE_6__*,size_t,size_t) ; 

int32_t dwc_otg_hcd_handle_rx_status_q_level_intr(dwc_otg_hcd_t * dwc_otg_hcd)
{
	host_grxsts_data_t grxsts;
	dwc_hc_t *hc = NULL;

	DWC_DEBUGPL(DBG_HCD, "--RxStsQ Level Interrupt--\n");

	grxsts.d32 =
	    DWC_READ_REG32(&dwc_otg_hcd->core_if->core_global_regs->grxstsp);

	hc = dwc_otg_hcd->hc_ptr_array[grxsts.b.chnum];
	if (!hc) {
		DWC_ERROR("Unable to get corresponding channel\n");
		return 0;
	}

	/* Packet Status */
	DWC_DEBUGPL(DBG_HCDV, "    Ch num = %d\n", grxsts.b.chnum);
	DWC_DEBUGPL(DBG_HCDV, "    Count = %d\n", grxsts.b.bcnt);
	DWC_DEBUGPL(DBG_HCDV, "    DPID = %d, hc.dpid = %d\n", grxsts.b.dpid,
		    hc->data_pid_start);
	DWC_DEBUGPL(DBG_HCDV, "    PStatus = %d\n", grxsts.b.pktsts);

	switch (grxsts.b.pktsts) {
	case DWC_GRXSTS_PKTSTS_IN:
		/* Read the data into the host buffer. */
		if (grxsts.b.bcnt > 0) {
			dwc_otg_read_packet(dwc_otg_hcd->core_if,
					    hc->xfer_buff, grxsts.b.bcnt);

			/* Update the HC fields for the next packet received. */
			hc->xfer_count += grxsts.b.bcnt;
			hc->xfer_buff += grxsts.b.bcnt;
		}

	case DWC_GRXSTS_PKTSTS_IN_XFER_COMP:
	case DWC_GRXSTS_PKTSTS_DATA_TOGGLE_ERR:
	case DWC_GRXSTS_PKTSTS_CH_HALTED:
		/* Handled in interrupt, just ignore data */
		break;
	default:
		DWC_ERROR("RX_STS_Q Interrupt: Unknown status %d\n",
			  grxsts.b.pktsts);
		break;
	}

	return 1;
}
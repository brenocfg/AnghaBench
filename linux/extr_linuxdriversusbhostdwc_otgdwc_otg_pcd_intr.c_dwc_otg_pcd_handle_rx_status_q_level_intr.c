#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_12__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
typedef  int int32_t ;
struct TYPE_27__ {int rxstsqlvl; } ;
struct TYPE_28__ {scalar_t__ d32; TYPE_5__ b; } ;
typedef  TYPE_6__ gintsts_data_t ;
struct TYPE_23__ {int rxstsqlvl; } ;
struct TYPE_29__ {int /*<<< orphan*/  d32; TYPE_1__ b; } ;
typedef  TYPE_7__ gintmsk_data_t ;
struct TYPE_30__ {TYPE_2__* setup_pkt; } ;
typedef  TYPE_8__ dwc_otg_pcd_t ;
struct TYPE_25__ {int /*<<< orphan*/  xfer_count; int /*<<< orphan*/  xfer_buff; } ;
struct TYPE_31__ {TYPE_3__ dwc_ep; } ;
typedef  TYPE_9__ dwc_otg_pcd_ep_t ;
struct TYPE_20__ {TYPE_11__* core_global_regs; } ;
typedef  TYPE_10__ dwc_otg_core_if_t ;
struct TYPE_21__ {int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gintmsk; int /*<<< orphan*/  grxstsp; } ;
typedef  TYPE_11__ dwc_otg_core_global_regs_t ;
struct TYPE_26__ {size_t dpid; int pktsts; int /*<<< orphan*/  bcnt; int /*<<< orphan*/  epnum; int /*<<< orphan*/  fn; } ;
struct TYPE_22__ {TYPE_4__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_12__ device_grxsts_data_t ;
struct TYPE_24__ {int /*<<< orphan*/  d32; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DBG_PCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,...) ; 
#define  DWC_DSTS_GOUT_NAK 132 
#define  DWC_DSTS_SETUP_COMP 131 
#define  DWC_DSTS_SETUP_UPDT 130 
 int /*<<< orphan*/  DWC_MODIFY_REG32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
#define  DWC_STS_DATA_UPDT 129 
#define  DWC_STS_XFER_COMP 128 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_10__* GET_CORE_IF (TYPE_8__*) ; 
 int /*<<< orphan*/ * dpid_str ; 
 int /*<<< orphan*/  dwc_otg_read_packet (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwc_otg_read_setup_packet (TYPE_10__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* get_out_ep (TYPE_8__*,int /*<<< orphan*/ ) ; 

int32_t dwc_otg_pcd_handle_rx_status_q_level_intr(dwc_otg_pcd_t * pcd)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	dwc_otg_core_global_regs_t *global_regs = core_if->core_global_regs;
	gintmsk_data_t gintmask = {.d32 = 0 };
	device_grxsts_data_t status;
	dwc_otg_pcd_ep_t *ep;
	gintsts_data_t gintsts;
#ifdef DEBUG
	static char *dpid_str[] = { "D0", "D2", "D1", "MDATA" };
#endif

	//DWC_DEBUGPL(DBG_PCDV, "%s(%p)\n", __func__, _pcd);
	/* Disable the Rx Status Queue Level interrupt */
	gintmask.b.rxstsqlvl = 1;
	DWC_MODIFY_REG32(&global_regs->gintmsk, gintmask.d32, 0);

	/* Get the Status from the top of the FIFO */
	status.d32 = DWC_READ_REG32(&global_regs->grxstsp);

	DWC_DEBUGPL(DBG_PCD, "EP:%d BCnt:%d DPID:%s "
		    "pktsts:%x Frame:%d(0x%0x)\n",
		    status.b.epnum, status.b.bcnt,
		    dpid_str[status.b.dpid],
		    status.b.pktsts, status.b.fn, status.b.fn);
	/* Get pointer to EP structure */
	ep = get_out_ep(pcd, status.b.epnum);

	switch (status.b.pktsts) {
	case DWC_DSTS_GOUT_NAK:
		DWC_DEBUGPL(DBG_PCDV, "Global OUT NAK\n");
		break;
	case DWC_STS_DATA_UPDT:
		DWC_DEBUGPL(DBG_PCDV, "OUT Data Packet\n");
		if (status.b.bcnt && ep->dwc_ep.xfer_buff) {
			/** @todo NGS Check for buffer overflow? */
			dwc_otg_read_packet(core_if,
					    ep->dwc_ep.xfer_buff,
					    status.b.bcnt);
			ep->dwc_ep.xfer_count += status.b.bcnt;
			ep->dwc_ep.xfer_buff += status.b.bcnt;
		}
		break;
	case DWC_STS_XFER_COMP:
		DWC_DEBUGPL(DBG_PCDV, "OUT Complete\n");
		break;
	case DWC_DSTS_SETUP_COMP:
#ifdef DEBUG_EP0
		DWC_DEBUGPL(DBG_PCDV, "Setup Complete\n");
#endif
		break;
	case DWC_DSTS_SETUP_UPDT:
		dwc_otg_read_setup_packet(core_if, pcd->setup_pkt->d32);
#ifdef DEBUG_EP0
		DWC_DEBUGPL(DBG_PCD,
			    "SETUP PKT: %02x.%02x v%04x i%04x l%04x\n",
			    pcd->setup_pkt->req.bmRequestType,
			    pcd->setup_pkt->req.bRequest,
			    UGETW(pcd->setup_pkt->req.wValue),
			    UGETW(pcd->setup_pkt->req.wIndex),
			    UGETW(pcd->setup_pkt->req.wLength));
#endif
		ep->dwc_ep.xfer_count += status.b.bcnt;
		break;
	default:
		DWC_DEBUGPL(DBG_PCDV, "Invalid Packet Status (0x%0x)\n",
			    status.b.pktsts);
		break;
	}

	/* Enable the Rx Status Queue Level interrupt */
	DWC_MODIFY_REG32(&global_regs->gintmsk, 0, gintmask.d32);
	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.rxstsqlvl = 1;
	DWC_WRITE_REG32(&global_regs->gintsts, gintsts.d32);

	//DWC_DEBUGPL(DBG_PCDV, "EXIT: %s\n", __func__);
	return 1;
}
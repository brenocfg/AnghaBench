#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_16__ {scalar_t__ nptxqspcavail; int nptxfspcavail; } ;
struct TYPE_18__ {int d32; TYPE_2__ b; } ;
typedef  TYPE_4__ gnptxsts_data_t ;
struct TYPE_17__ {int nptxfempty; } ;
struct TYPE_19__ {scalar_t__ d32; TYPE_3__ b; } ;
typedef  TYPE_5__ gintsts_data_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_14__ {int xfer_len; int xfer_count; int maxpacket; } ;
struct TYPE_20__ {TYPE_12__ dwc_ep; } ;
typedef  TYPE_6__ dwc_otg_pcd_ep_t ;
typedef  int /*<<< orphan*/  dwc_otg_dev_in_ep_regs_t ;
struct TYPE_21__ {TYPE_1__* dev_if; TYPE_8__* core_global_regs; } ;
typedef  TYPE_7__ dwc_otg_core_if_t ;
struct TYPE_22__ {int /*<<< orphan*/  gintsts; int /*<<< orphan*/  gnptxsts; } ;
typedef  TYPE_8__ dwc_otg_core_global_regs_t ;
struct TYPE_15__ {int /*<<< orphan*/ ** in_ep_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DBG_PCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,int) ; 
 int DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DWC_WRITE_REG32 (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_7__* GET_CORE_IF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_ep_write_packet (TYPE_7__*,TYPE_12__*,int /*<<< orphan*/ ) ; 
 int get_ep_of_last_in_token (TYPE_7__*) ; 
 TYPE_6__* get_in_ep (int /*<<< orphan*/ *,int) ; 

int32_t dwc_otg_pcd_handle_np_tx_fifo_empty_intr(dwc_otg_pcd_t * pcd)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	dwc_otg_core_global_regs_t *global_regs = core_if->core_global_regs;
	dwc_otg_dev_in_ep_regs_t *ep_regs;
	gnptxsts_data_t txstatus = {.d32 = 0 };
	gintsts_data_t gintsts;

	int epnum = 0;
	dwc_otg_pcd_ep_t *ep = 0;
	uint32_t len = 0;
	int dwords;

	/* Get the epnum from the IN Token Learning Queue. */
	epnum = get_ep_of_last_in_token(core_if);
	ep = get_in_ep(pcd, epnum);

	DWC_DEBUGPL(DBG_PCD, "NP TxFifo Empty: %d \n", epnum);

	ep_regs = core_if->dev_if->in_ep_regs[epnum];

	len = ep->dwc_ep.xfer_len - ep->dwc_ep.xfer_count;
	if (len > ep->dwc_ep.maxpacket) {
		len = ep->dwc_ep.maxpacket;
	}
	dwords = (len + 3) / 4;

	/* While there is space in the queue and space in the FIFO and
	 * More data to tranfer, Write packets to the Tx FIFO */
	txstatus.d32 = DWC_READ_REG32(&global_regs->gnptxsts);
	DWC_DEBUGPL(DBG_PCDV, "b4 GNPTXSTS=0x%08x\n", txstatus.d32);

	while (txstatus.b.nptxqspcavail > 0 &&
	       txstatus.b.nptxfspcavail > dwords &&
	       ep->dwc_ep.xfer_count < ep->dwc_ep.xfer_len) {
		/* Write the FIFO */
		dwc_otg_ep_write_packet(core_if, &ep->dwc_ep, 0);
		len = ep->dwc_ep.xfer_len - ep->dwc_ep.xfer_count;

		if (len > ep->dwc_ep.maxpacket) {
			len = ep->dwc_ep.maxpacket;
		}

		dwords = (len + 3) / 4;
		txstatus.d32 = DWC_READ_REG32(&global_regs->gnptxsts);
		DWC_DEBUGPL(DBG_PCDV, "GNPTXSTS=0x%08x\n", txstatus.d32);
	}

	DWC_DEBUGPL(DBG_PCDV, "GNPTXSTS=0x%08x\n",
		    DWC_READ_REG32(&global_regs->gnptxsts));

	/* Clear interrupt */
	gintsts.d32 = 0;
	gintsts.b.nptxfempty = 1;
	DWC_WRITE_REG32(&global_regs->gintsts, gintsts.d32);

	return 1;
}
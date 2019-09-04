#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_17__ {size_t xfer_len; size_t xfer_count; size_t maxpacket; } ;
struct TYPE_12__ {TYPE_9__ dwc_ep; } ;
typedef  TYPE_2__ dwc_otg_pcd_ep_t ;
struct TYPE_13__ {int /*<<< orphan*/  dtxfsts; } ;
typedef  TYPE_3__ dwc_otg_dev_in_ep_regs_t ;
struct TYPE_14__ {TYPE_3__** in_ep_regs; } ;
typedef  TYPE_4__ dwc_otg_dev_if_t ;
struct TYPE_15__ {TYPE_4__* dev_if; } ;
typedef  TYPE_5__ dwc_otg_core_if_t ;
struct TYPE_11__ {int txfspcavail; } ;
struct TYPE_16__ {void* d32; TYPE_1__ b; } ;
typedef  TYPE_6__ dtxfsts_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DBG_PCDV ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,size_t,...) ; 
 void* DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 TYPE_5__* GET_CORE_IF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_ep_write_packet (TYPE_5__*,TYPE_9__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_in_ep (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int32_t write_empty_tx_fifo(dwc_otg_pcd_t * pcd, uint32_t epnum)
{
	dwc_otg_core_if_t *core_if = GET_CORE_IF(pcd);
	dwc_otg_dev_if_t *dev_if = core_if->dev_if;
	dwc_otg_dev_in_ep_regs_t *ep_regs;
	dtxfsts_data_t txstatus = {.d32 = 0 };
	dwc_otg_pcd_ep_t *ep = 0;
	uint32_t len = 0;
	int dwords;

	ep = get_in_ep(pcd, epnum);

	DWC_DEBUGPL(DBG_PCD, "Dedicated TxFifo Empty: %d \n", epnum);

	ep_regs = core_if->dev_if->in_ep_regs[epnum];

	len = ep->dwc_ep.xfer_len - ep->dwc_ep.xfer_count;

	if (len > ep->dwc_ep.maxpacket) {
		len = ep->dwc_ep.maxpacket;
	}

	dwords = (len + 3) / 4;

	/* While there is space in the queue and space in the FIFO and
	 * More data to tranfer, Write packets to the Tx FIFO */
	txstatus.d32 = DWC_READ_REG32(&dev_if->in_ep_regs[epnum]->dtxfsts);
	DWC_DEBUGPL(DBG_PCDV, "b4 dtxfsts[%d]=0x%08x\n", epnum, txstatus.d32);

	while (txstatus.b.txfspcavail > dwords &&
	       ep->dwc_ep.xfer_count < ep->dwc_ep.xfer_len &&
	       ep->dwc_ep.xfer_len != 0) {
		/* Write the FIFO */
		dwc_otg_ep_write_packet(core_if, &ep->dwc_ep, 0);

		len = ep->dwc_ep.xfer_len - ep->dwc_ep.xfer_count;
		if (len > ep->dwc_ep.maxpacket) {
			len = ep->dwc_ep.maxpacket;
		}

		dwords = (len + 3) / 4;
		txstatus.d32 =
		    DWC_READ_REG32(&dev_if->in_ep_regs[epnum]->dtxfsts);
		DWC_DEBUGPL(DBG_PCDV, "dtxfsts[%d]=0x%08x\n", epnum,
			    txstatus.d32);
	}

	DWC_DEBUGPL(DBG_PCDV, "b4 dtxfsts[%d]=0x%08x\n", epnum,
		    DWC_READ_REG32(&dev_if->in_ep_regs[epnum]->dtxfsts));

	return 1;
}
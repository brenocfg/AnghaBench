#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  dwc_otg_pcd_t ;
struct TYPE_19__ {scalar_t__ xfer_buff; scalar_t__ xfer_count; scalar_t__ xfer_len; scalar_t__ start_xfer_buff; scalar_t__ total_len; scalar_t__ maxpacket; } ;
struct TYPE_15__ {TYPE_9__ dwc_ep; scalar_t__ stopped; } ;
typedef  TYPE_3__ dwc_otg_pcd_ep_t ;
struct TYPE_16__ {TYPE_1__** in_ep_regs; } ;
typedef  TYPE_4__ dwc_otg_dev_if_t ;
struct TYPE_17__ {TYPE_4__* dev_if; } ;
typedef  TYPE_5__ dwc_otg_core_if_t ;
struct TYPE_14__ {scalar_t__ xfersize; scalar_t__ pktcnt; } ;
struct TYPE_18__ {TYPE_2__ b; int /*<<< orphan*/  d32; } ;
typedef  TYPE_6__ deptsiz_data_t ;
struct TYPE_13__ {int /*<<< orphan*/  dieptsiz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_PCD ; 
 int /*<<< orphan*/  DWC_DEBUGPL (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DWC_READ_REG32 (int /*<<< orphan*/ *) ; 
 TYPE_5__* GET_CORE_IF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc_otg_ep0_start_transfer (TYPE_5__*,TYPE_9__*) ; 
 int /*<<< orphan*/  dwc_otg_ep_start_transfer (TYPE_5__*,TYPE_9__*) ; 
 TYPE_3__* get_in_ep (int /*<<< orphan*/ *,size_t const) ; 

__attribute__((used)) static void restart_transfer(dwc_otg_pcd_t * pcd, const uint32_t epnum)
{
	dwc_otg_core_if_t *core_if;
	dwc_otg_dev_if_t *dev_if;
	deptsiz_data_t dieptsiz = {.d32 = 0 };
	dwc_otg_pcd_ep_t *ep;

	ep = get_in_ep(pcd, epnum);

#ifdef DWC_EN_ISOC
	if (ep->dwc_ep.type == DWC_OTG_EP_TYPE_ISOC) {
		return;
	}
#endif /* DWC_EN_ISOC  */

	core_if = GET_CORE_IF(pcd);
	dev_if = core_if->dev_if;

	dieptsiz.d32 = DWC_READ_REG32(&dev_if->in_ep_regs[epnum]->dieptsiz);

	DWC_DEBUGPL(DBG_PCD, "xfer_buff=%p xfer_count=%0x xfer_len=%0x"
		    " stopped=%d\n", ep->dwc_ep.xfer_buff,
		    ep->dwc_ep.xfer_count, ep->dwc_ep.xfer_len, ep->stopped);
	/*
	 * If xfersize is 0 and pktcnt in not 0, resend the last packet.
	 */
	if (dieptsiz.b.pktcnt && dieptsiz.b.xfersize == 0 &&
	    ep->dwc_ep.start_xfer_buff != 0) {
		if (ep->dwc_ep.total_len <= ep->dwc_ep.maxpacket) {
			ep->dwc_ep.xfer_count = 0;
			ep->dwc_ep.xfer_buff = ep->dwc_ep.start_xfer_buff;
			ep->dwc_ep.xfer_len = ep->dwc_ep.xfer_count;
		} else {
			ep->dwc_ep.xfer_count -= ep->dwc_ep.maxpacket;
			/* convert packet size to dwords. */
			ep->dwc_ep.xfer_buff -= ep->dwc_ep.maxpacket;
			ep->dwc_ep.xfer_len = ep->dwc_ep.xfer_count;
		}
		ep->stopped = 0;
		DWC_DEBUGPL(DBG_PCD, "xfer_buff=%p xfer_count=%0x "
			    "xfer_len=%0x stopped=%d\n",
			    ep->dwc_ep.xfer_buff,
			    ep->dwc_ep.xfer_count, ep->dwc_ep.xfer_len,
			    ep->stopped);
		if (epnum == 0) {
			dwc_otg_ep0_start_transfer(core_if, &ep->dwc_ep);
		} else {
			dwc_otg_ep_start_transfer(core_if, &ep->dwc_ep);
		}
	}
}
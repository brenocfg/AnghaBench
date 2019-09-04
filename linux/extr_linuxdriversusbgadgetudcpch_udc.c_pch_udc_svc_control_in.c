#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pch_udc_ep {int epsts; TYPE_1__* td_data; } ;
struct pch_udc_dev {int /*<<< orphan*/  stall; struct pch_udc_ep* ep; } ;
struct TYPE_2__ {int status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DIR_RX ; 
 int PCH_UDC_BS_HST_RDY ; 
 int PCH_UDC_BUFF_STS ; 
 size_t UDC_EP0IN_IDX ; 
 size_t UDC_EP0OUT_IDX ; 
 int UDC_EPSTS_BNA ; 
 int UDC_EPSTS_HE ; 
 int UDC_EPSTS_IN ; 
 int UDC_EPSTS_RCS ; 
 int UDC_EPSTS_TDC ; 
 int UDC_EPSTS_TXEMPTY ; 
 int UDC_EPSTS_XFERDONE ; 
 int /*<<< orphan*/  pch_udc_clear_dma (struct pch_udc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_udc_complete_transfer (struct pch_udc_ep*) ; 
 int /*<<< orphan*/  pch_udc_ep_clear_nak (struct pch_udc_ep*) ; 
 int /*<<< orphan*/  pch_udc_ep_set_rrdy (struct pch_udc_ep*) ; 
 int /*<<< orphan*/  pch_udc_set_dma (struct pch_udc_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_udc_start_next_txrequest (struct pch_udc_ep*) ; 

__attribute__((used)) static void pch_udc_svc_control_in(struct pch_udc_dev *dev)
{
	u32	epsts;
	struct pch_udc_ep	*ep;
	struct pch_udc_ep	*ep_out;

	ep = &dev->ep[UDC_EP0IN_IDX];
	ep_out = &dev->ep[UDC_EP0OUT_IDX];
	epsts = ep->epsts;
	ep->epsts = 0;

	if (!(epsts & (UDC_EPSTS_IN | UDC_EPSTS_BNA | UDC_EPSTS_HE |
		       UDC_EPSTS_TDC | UDC_EPSTS_RCS | UDC_EPSTS_TXEMPTY |
		       UDC_EPSTS_XFERDONE)))
		return;
	if ((epsts & UDC_EPSTS_BNA))
		return;
	if (epsts & UDC_EPSTS_HE)
		return;
	if ((epsts & UDC_EPSTS_TDC) && (!dev->stall)) {
		pch_udc_complete_transfer(ep);
		pch_udc_clear_dma(dev, DMA_DIR_RX);
		ep_out->td_data->status = (ep_out->td_data->status &
					~PCH_UDC_BUFF_STS) |
					PCH_UDC_BS_HST_RDY;
		pch_udc_ep_clear_nak(ep_out);
		pch_udc_set_dma(dev, DMA_DIR_RX);
		pch_udc_ep_set_rrdy(ep_out);
	}
	/* On IN interrupt, provide data if we have any */
	if ((epsts & UDC_EPSTS_IN) && !(epsts & UDC_EPSTS_TDC) &&
	     !(epsts & UDC_EPSTS_TXEMPTY))
		pch_udc_start_next_txrequest(ep);
}
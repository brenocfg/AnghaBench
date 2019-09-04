#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nbu2ss_udc {TYPE_4__* p_regs; } ;
struct TYPE_5__ {int maxpacket; } ;
struct nbu2ss_ep {int epnum; scalar_t__ direct; TYPE_1__ ep; } ;
struct TYPE_8__ {TYPE_3__* EP_REGS; TYPE_2__* EP_DCR; int /*<<< orphan*/  USBSSCONF; } ;
struct TYPE_7__ {int /*<<< orphan*/  EP_DMA_CTRL; int /*<<< orphan*/  EP_CONTROL; } ;
struct TYPE_6__ {int /*<<< orphan*/  EP_DCR1; int /*<<< orphan*/  EP_DCR2; } ;

/* Variables and functions */
 int DCR1_EPN_DIR0 ; 
 int EPN_AUTO ; 
 int EPN_BURST_SET ; 
 int EPN_DMAMODE0 ; 
 int EPN_STOP_MODE ; 
 int EPN_STOP_SET ; 
 scalar_t__ USB_DIR_OUT ; 
 int /*<<< orphan*/  _nbu2ss_bitset (int /*<<< orphan*/ *,int) ; 
 int _nbu2ss_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _nbu2ss_ep_dma_init(struct nbu2ss_udc *udc, struct nbu2ss_ep *ep)
{
	u32		num;
	u32		data;

	data = _nbu2ss_readl(&udc->p_regs->USBSSCONF);
	if (((ep->epnum == 0) || (data & (1 << ep->epnum)) == 0))
		return;		/* Not Support DMA */

	num = ep->epnum - 1;

	if (ep->direct == USB_DIR_OUT) {
		/*---------------------------------------------------------*/
		/* OUT */
		data = ep->ep.maxpacket;
		_nbu2ss_writel(&udc->p_regs->EP_DCR[num].EP_DCR2, data);

		/*---------------------------------------------------------*/
		/* Transfer Direct */
		data = DCR1_EPN_DIR0;
		_nbu2ss_bitset(&udc->p_regs->EP_DCR[num].EP_DCR1, data);

		/*---------------------------------------------------------*/
		/* DMA Mode etc. */
		data = EPN_STOP_MODE | EPN_STOP_SET  | EPN_DMAMODE0;
		_nbu2ss_writel(&udc->p_regs->EP_REGS[num].EP_DMA_CTRL, data);
	} else {
		/*---------------------------------------------------------*/
		/* IN */
		_nbu2ss_bitset(&udc->p_regs->EP_REGS[num].EP_CONTROL, EPN_AUTO);

		/*---------------------------------------------------------*/
		/* DMA Mode etc. */
		data = EPN_BURST_SET | EPN_DMAMODE0;
		_nbu2ss_writel(&udc->p_regs->EP_REGS[num].EP_DMA_CTRL, data);
	}
}
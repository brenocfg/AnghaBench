#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nbu2ss_udc {scalar_t__ vbus_active; struct fc_regs* p_regs; } ;
struct nbu2ss_ep {int epnum; scalar_t__ direct; } ;
struct fc_regs {TYPE_2__* EP_REGS; TYPE_1__* EP_DCR; int /*<<< orphan*/  USBSSCONF; } ;
struct TYPE_4__ {int /*<<< orphan*/  EP_DMA_CTRL; int /*<<< orphan*/  EP_CONTROL; } ;
struct TYPE_3__ {int /*<<< orphan*/  EP_DCR1; int /*<<< orphan*/  EP_DCR2; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCR1_EPN_DIR0 ; 
 int /*<<< orphan*/  EPN_AUTO ; 
 scalar_t__ USB_DIR_OUT ; 
 int /*<<< orphan*/  _nbu2ss_bitclr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nbu2ss_ep_dma_abort (struct nbu2ss_udc*,struct nbu2ss_ep*) ; 
 int _nbu2ss_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _nbu2ss_ep_dma_exit(struct nbu2ss_udc *udc, struct nbu2ss_ep *ep)
{
	u32		num;
	u32		data;
	struct fc_regs	*preg = udc->p_regs;

	if (udc->vbus_active == 0)
		return;		/* VBUS OFF */

	data = _nbu2ss_readl(&preg->USBSSCONF);
	if ((ep->epnum == 0) || ((data & (1 << ep->epnum)) == 0))
		return;		/* Not Support DMA */

	num = ep->epnum - 1;

	_nbu2ss_ep_dma_abort(udc, ep);

	if (ep->direct == USB_DIR_OUT) {
		/*---------------------------------------------------------*/
		/* OUT */
		_nbu2ss_writel(&preg->EP_DCR[num].EP_DCR2, 0);
		_nbu2ss_bitclr(&preg->EP_DCR[num].EP_DCR1, DCR1_EPN_DIR0);
		_nbu2ss_writel(&preg->EP_REGS[num].EP_DMA_CTRL, 0);
	} else {
		/*---------------------------------------------------------*/
		/* IN */
		_nbu2ss_bitclr(&preg->EP_REGS[num].EP_CONTROL, EPN_AUTO);
		_nbu2ss_writel(&preg->EP_REGS[num].EP_DMA_CTRL, 0);
	}
}
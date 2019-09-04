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
struct nbu2ss_udc {struct fc_regs* p_regs; } ;
struct nbu2ss_ep {int epnum; } ;
struct fc_regs {TYPE_2__* EP_REGS; TYPE_1__* EP_DCR; } ;
struct TYPE_4__ {int /*<<< orphan*/  EP_DMA_CTRL; } ;
struct TYPE_3__ {int /*<<< orphan*/  EP_DCR1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCR1_EPN_REQEN ; 
 int /*<<< orphan*/  DMA_DISABLE_TIME ; 
 int /*<<< orphan*/  EPN_DMA_EN ; 
 int /*<<< orphan*/  _nbu2ss_bitclr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _nbu2ss_ep_dma_abort(struct nbu2ss_udc *udc, struct nbu2ss_ep *ep)
{
	struct fc_regs	*preg = udc->p_regs;

	_nbu2ss_bitclr(&preg->EP_DCR[ep->epnum - 1].EP_DCR1, DCR1_EPN_REQEN);
	mdelay(DMA_DISABLE_TIME);	/* DCR1_EPN_REQEN Clear */
	_nbu2ss_bitclr(&preg->EP_REGS[ep->epnum - 1].EP_DMA_CTRL, EPN_DMA_EN);
}
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
struct nbu2ss_udc {scalar_t__ vbus_active; struct fc_regs* p_regs; } ;
struct nbu2ss_ep {int epnum; } ;
struct fc_regs {TYPE_1__* EP_REGS; int /*<<< orphan*/  EP0_CONTROL; } ;
struct TYPE_2__ {int /*<<< orphan*/  EP_CONTROL; } ;

/* Variables and functions */
 int /*<<< orphan*/  EP0_BCLR ; 
 int /*<<< orphan*/  EPN_BCLR ; 
 int /*<<< orphan*/  _nbu2ss_bitset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nbu2ss_ep_dma_abort (struct nbu2ss_udc*,struct nbu2ss_ep*) ; 

__attribute__((used)) static void _nbu2ss_fifo_flush(struct nbu2ss_udc *udc, struct nbu2ss_ep *ep)
{
	struct fc_regs	*p = udc->p_regs;

	if (udc->vbus_active == 0)
		return;

	if (ep->epnum == 0) {
		/* EP0 */
		_nbu2ss_bitset(&p->EP0_CONTROL, EP0_BCLR);

	} else {
		/* EPN */
		_nbu2ss_ep_dma_abort(udc, ep);
		_nbu2ss_bitset(&p->EP_REGS[ep->epnum - 1].EP_CONTROL, EPN_BCLR);
	}
}
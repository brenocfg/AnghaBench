#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nbu2ss_udc {struct fc_regs* p_regs; } ;
struct TYPE_4__ {int actual; int length; } ;
struct nbu2ss_req {int zero; TYPE_1__ req; scalar_t__ div_len; scalar_t__ dma_flag; } ;
struct TYPE_5__ {int maxpacket; } ;
struct nbu2ss_ep {int epnum; TYPE_2__ ep; } ;
struct fc_regs {TYPE_3__* EP_REGS; } ;
struct TYPE_6__ {int /*<<< orphan*/  EP_STATUS; } ;

/* Variables and functions */
 int EPN_IN_FULL ; 
 int /*<<< orphan*/  _nbu2ss_ep_done (struct nbu2ss_ep*,struct nbu2ss_req*,int) ; 
 int _nbu2ss_epn_in_transfer (struct nbu2ss_udc*,struct nbu2ss_ep*,struct nbu2ss_req*) ; 
 int _nbu2ss_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nbu2ss_zero_len_pkt (struct nbu2ss_udc*,int) ; 

__attribute__((used)) static inline void _nbu2ss_epn_in_int(
	struct nbu2ss_udc *udc,
	struct nbu2ss_ep *ep,
	struct nbu2ss_req *req)
{
	int	result = 0;
	u32	status;

	struct fc_regs	*preg = udc->p_regs;

	if (req->dma_flag)
		return;		/* DMA is forwarded */

	req->req.actual += req->div_len;
	req->div_len = 0;

	if (req->req.actual != req->req.length) {
		/*---------------------------------------------------------*/
		/* remainder of data */
		result = _nbu2ss_epn_in_transfer(udc, ep, req);

	} else {
		if (req->zero && ((req->req.actual % ep->ep.maxpacket) == 0)) {
			status =
			_nbu2ss_readl(&preg->EP_REGS[ep->epnum - 1].EP_STATUS);

			if ((status & EPN_IN_FULL) == 0) {
				/*-----------------------------------------*/
				/* 0 Length Packet */
				req->zero = false;
				_nbu2ss_zero_len_pkt(udc, ep->epnum);
			}
			return;
		}
	}

	if (result <= 0) {
		/*---------------------------------------------------------*/
		/* Complete */
		_nbu2ss_ep_done(ep, req, result);
	}
}
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
typedef  size_t u32 ;
struct nbu2ss_udc {struct fc_regs* p_regs; } ;
struct TYPE_8__ {int actual; int length; } ;
struct nbu2ss_req {size_t div_len; void* dma_flag; TYPE_4__ req; int /*<<< orphan*/  zero; } ;
struct TYPE_7__ {int maxpacket; } ;
struct nbu2ss_ep {size_t epnum; TYPE_3__ ep; } ;
struct fc_regs {TYPE_2__* EP_DCR; TYPE_1__* EP_REGS; } ;
struct TYPE_6__ {int /*<<< orphan*/  EP_DCR1; } ;
struct TYPE_5__ {int /*<<< orphan*/  EP_LEN_DCNT; } ;

/* Variables and functions */
 size_t DCR1_EPN_DMACNT ; 
 int /*<<< orphan*/  DCR1_EPN_REQEN ; 
 int EPC_PLL_LOCK_COUNT ; 
 size_t EPN_DMACNT ; 
 void* FALSE ; 
 int /*<<< orphan*/  _nbu2ss_bitclr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nbu2ss_ep_done (struct nbu2ss_ep*,struct nbu2ss_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nbu2ss_epn_out_int (struct nbu2ss_udc*,struct nbu2ss_ep*,struct nbu2ss_req*) ; 
 size_t _nbu2ss_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void _nbu2ss_epn_out_dma_int(
	struct nbu2ss_udc *udc,
	struct nbu2ss_ep *ep,
	struct nbu2ss_req *req)
{
	int		i;
	u32		num;
	u32		dmacnt, ep_dmacnt;
	u32		mpkt;
	struct fc_regs	*preg = udc->p_regs;

	num = ep->epnum - 1;

	if (req->req.actual == req->req.length) {
		if ((req->req.length % ep->ep.maxpacket) && !req->zero) {
			req->div_len = 0;
			req->dma_flag = FALSE;
			_nbu2ss_ep_done(ep, req, 0);
			return;
		}
	}

	ep_dmacnt = _nbu2ss_readl(&preg->EP_REGS[num].EP_LEN_DCNT)
		 & EPN_DMACNT;
	ep_dmacnt >>= 16;

	for (i = 0; i < EPC_PLL_LOCK_COUNT; i++) {
		dmacnt = _nbu2ss_readl(&preg->EP_DCR[num].EP_DCR1)
			 & DCR1_EPN_DMACNT;
		dmacnt >>= 16;
		if (ep_dmacnt == dmacnt)
			break;
	}

	_nbu2ss_bitclr(&preg->EP_DCR[num].EP_DCR1, DCR1_EPN_REQEN);

	if (dmacnt != 0) {
		mpkt = ep->ep.maxpacket;
		if ((req->div_len % mpkt) == 0)
			req->div_len -= mpkt * dmacnt;
	}

	if ((req->req.actual % ep->ep.maxpacket) > 0) {
		if (req->req.actual == req->div_len) {
			req->div_len = 0;
			req->dma_flag = FALSE;
			_nbu2ss_ep_done(ep, req, 0);
			return;
		}
	}

	req->req.actual += req->div_len;
	req->div_len = 0;
	req->dma_flag = FALSE;

	_nbu2ss_epn_out_int(udc, ep, req);
}
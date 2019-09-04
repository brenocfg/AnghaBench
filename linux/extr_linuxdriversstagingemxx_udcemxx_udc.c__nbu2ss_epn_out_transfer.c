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
typedef  size_t u32 ;
struct nbu2ss_udc {int /*<<< orphan*/  dev; struct fc_regs* p_regs; } ;
struct TYPE_6__ {int actual; int length; } ;
struct nbu2ss_req {int zero; TYPE_3__ req; } ;
struct TYPE_5__ {size_t maxpacket; } ;
struct nbu2ss_ep {scalar_t__ epnum; TYPE_2__ ep; } ;
struct fc_regs {TYPE_1__* EP_REGS; } ;
struct TYPE_4__ {int /*<<< orphan*/  EP_LEN_DCNT; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOVERFLOW ; 
 size_t EPN_LDATA ; 
 int _nbu2ss_epn_out_data (struct nbu2ss_udc*,struct nbu2ss_ep*,struct nbu2ss_req*,size_t) ; 
 size_t _nbu2ss_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int _nbu2ss_epn_out_transfer(
	struct nbu2ss_udc *udc,
	struct nbu2ss_ep *ep,
	struct nbu2ss_req *req
)
{
	u32		num;
	u32		i_recv_length;
	int		result = 1;
	struct fc_regs	*preg = udc->p_regs;

	if (ep->epnum == 0)
		return -EINVAL;

	num = ep->epnum - 1;

	/*-------------------------------------------------------------*/
	/* Receive Length */
	i_recv_length
		= _nbu2ss_readl(&preg->EP_REGS[num].EP_LEN_DCNT) & EPN_LDATA;

	if (i_recv_length != 0) {
		result = _nbu2ss_epn_out_data(udc, ep, req, i_recv_length);
		if (i_recv_length < ep->ep.maxpacket) {
			if (i_recv_length == result) {
				req->req.actual += result;
				result = 0;
			}
		}
	} else {
		if ((req->req.actual == req->req.length) ||
		    ((req->req.actual % ep->ep.maxpacket) != 0)) {
			result = 0;
		}
	}

	if (result == 0) {
		if ((req->req.actual % ep->ep.maxpacket) == 0) {
			if (req->zero) {
				req->zero = false;
				return 1;
			}
		}
	}

	if (req->req.actual > req->req.length) {
		dev_err(udc->dev, " Overrun Error\n");
		dev_err(udc->dev, " actual = %d, length = %d\n",
			req->req.actual, req->req.length);
		result = -EOVERFLOW;
	}

	return result;
}
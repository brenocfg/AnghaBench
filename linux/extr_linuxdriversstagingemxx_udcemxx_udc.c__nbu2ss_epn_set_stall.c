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
typedef  int u8 ;
typedef  int u32 ;
struct nbu2ss_udc {struct fc_regs* p_regs; } ;
struct nbu2ss_ep {int direct; int epnum; } ;
struct fc_regs {TYPE_1__* EP_REGS; } ;
struct TYPE_2__ {int /*<<< orphan*/  EP_STATUS; } ;

/* Variables and functions */
 int EPN_IN_DATA ; 
 int IN_DATA_EMPTY_COUNT ; 
 int USB_DIR_IN ; 
 int _nbu2ss_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nbu2ss_set_endpoint_stall (struct nbu2ss_udc*,int,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static void _nbu2ss_epn_set_stall(
	struct nbu2ss_udc *udc,
	struct nbu2ss_ep *ep
)
{
	u8	ep_adrs;
	u32	regdata;
	int	limit_cnt = 0;

	struct fc_regs	*preg = udc->p_regs;

	if (ep->direct == USB_DIR_IN) {
		for (limit_cnt = 0
			; limit_cnt < IN_DATA_EMPTY_COUNT
			; limit_cnt++) {
			regdata = _nbu2ss_readl(
				&preg->EP_REGS[ep->epnum - 1].EP_STATUS);

			if ((regdata & EPN_IN_DATA) == 0)
				break;

			mdelay(1);
		}
	}

	ep_adrs = ep->epnum | ep->direct;
	_nbu2ss_set_endpoint_stall(udc, ep_adrs, 1);
}
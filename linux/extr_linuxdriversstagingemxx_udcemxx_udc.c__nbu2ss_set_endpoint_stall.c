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
struct nbu2ss_udc {struct nbu2ss_ep* ep; struct fc_regs* p_regs; } ;
struct nbu2ss_ep {void* halted; void* stalled; } ;
struct fc_regs {TYPE_1__* EP_REGS; int /*<<< orphan*/  EP0_CONTROL; } ;
struct TYPE_2__ {int /*<<< orphan*/  EP_CONTROL; } ;

/* Variables and functions */
 int EP0_STL ; 
 int EPN_BCLR ; 
 int EPN_ISTL ; 
 int EPN_OSTL ; 
 int EPN_OSTL_EN ; 
 void* FALSE ; 
 void* TRUE ; 
 int USB_DIR_IN ; 
 int USB_ENDPOINT_NUMBER_MASK ; 
 int /*<<< orphan*/  _nbu2ss_bitclr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _nbu2ss_bitset (int /*<<< orphan*/ *,int) ; 
 int _nbu2ss_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nbu2ss_restert_transfer (struct nbu2ss_ep*) ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _nbu2ss_set_endpoint_stall(
	struct nbu2ss_udc *udc,
	u8 ep_adrs,
	bool bstall)
{
	u8		num, epnum;
	u32		data;
	struct nbu2ss_ep *ep;
	struct fc_regs	*preg = udc->p_regs;

	if ((ep_adrs == 0) || (ep_adrs == 0x80)) {
		if (bstall) {
			/* Set STALL */
			_nbu2ss_bitset(&preg->EP0_CONTROL, EP0_STL);
		} else {
			/* Clear STALL */
			_nbu2ss_bitclr(&preg->EP0_CONTROL, EP0_STL);
		}
	} else {
		epnum = ep_adrs & USB_ENDPOINT_NUMBER_MASK;
		num = epnum - 1;
		ep = &udc->ep[epnum];

		if (bstall) {
			/* Set STALL */
			ep->halted = TRUE;

			if (ep_adrs & USB_DIR_IN)
				data = EPN_BCLR | EPN_ISTL;
			else
				data = EPN_OSTL_EN | EPN_OSTL;

			_nbu2ss_bitset(&preg->EP_REGS[num].EP_CONTROL, data);
		} else {
			/* Clear STALL */
			ep->stalled = FALSE;
			if (ep_adrs & USB_DIR_IN) {
				_nbu2ss_bitclr(&preg->EP_REGS[num].EP_CONTROL
						, EPN_ISTL);
			} else {
				data =
				_nbu2ss_readl(&preg->EP_REGS[num].EP_CONTROL);

				data &= ~EPN_OSTL;
				data |= EPN_OSTL_EN;

				_nbu2ss_writel(&preg->EP_REGS[num].EP_CONTROL
						, data);
			}

			ep->stalled = FALSE;
			if (ep->halted) {
				ep->halted = FALSE;
				_nbu2ss_restert_transfer(ep);
			}
		}
	}
}
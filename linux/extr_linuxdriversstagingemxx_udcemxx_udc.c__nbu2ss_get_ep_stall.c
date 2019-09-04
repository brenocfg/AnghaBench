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
struct fc_regs {TYPE_1__* EP_REGS; int /*<<< orphan*/  EP0_CONTROL; } ;
struct TYPE_2__ {int /*<<< orphan*/  EP_CONTROL; } ;

/* Variables and functions */
 int EP0_STL ; 
 int EPN_EN ; 
 int EPN_ISTL ; 
 int EPN_OSTL ; 
 int USB_ENDPOINT_DIR_MASK ; 
 int _nbu2ss_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _nbu2ss_get_ep_stall(struct nbu2ss_udc *udc, u8 ep_adrs)
{
	u8		epnum;
	u32		data = 0, bit_data;
	struct fc_regs	*preg = udc->p_regs;

	epnum = ep_adrs & ~USB_ENDPOINT_DIR_MASK;
	if (epnum == 0) {
		data = _nbu2ss_readl(&preg->EP0_CONTROL);
		bit_data = EP0_STL;

	} else {
		data = _nbu2ss_readl(&preg->EP_REGS[epnum - 1].EP_CONTROL);
		if ((data & EPN_EN) == 0)
			return -1;

		if (ep_adrs & USB_ENDPOINT_DIR_MASK)
			bit_data = EPN_ISTL;
		else
			bit_data = EPN_OSTL;
	}

	if ((data & bit_data) == 0)
		return 0;
	return 1;
}
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
typedef  int u32 ;
struct nbu2ss_udc {TYPE_1__* p_regs; } ;
struct ep_regs {int /*<<< orphan*/  EP_CONTROL; int /*<<< orphan*/  EP_PCKT_ADRS; } ;
struct TYPE_2__ {struct ep_regs* EP_REGS; } ;

/* Variables and functions */
 int D_RAM_SIZE_CTRL ; 
 int EPN_BUF_TYPE ; 
 int EPN_MPKT ; 
 int NUM_ENDPOINTS ; 
 int _nbu2ss_readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 _nbu2ss_get_begin_ram_address(struct nbu2ss_udc *udc)
{
	u32		num, buf_type;
	u32		data, last_ram_adr, use_ram_size;

	struct ep_regs *p_ep_regs;

	last_ram_adr = (D_RAM_SIZE_CTRL / sizeof(u32)) * 2;
	use_ram_size = 0;

	for (num = 0; num < NUM_ENDPOINTS - 1; num++) {
		p_ep_regs = &udc->p_regs->EP_REGS[num];
		data = _nbu2ss_readl(&p_ep_regs->EP_PCKT_ADRS);
		buf_type = _nbu2ss_readl(&p_ep_regs->EP_CONTROL) & EPN_BUF_TYPE;
		if (buf_type == 0) {
			/* Single Buffer */
			use_ram_size += (data & EPN_MPKT) / sizeof(u32);
		} else {
			/* Double Buffer */
			use_ram_size += ((data & EPN_MPKT) / sizeof(u32)) * 2;
		}

		if ((data >> 16) > last_ram_adr)
			last_ram_adr = data >> 16;
	}

	return last_ram_adr + use_ram_size;
}
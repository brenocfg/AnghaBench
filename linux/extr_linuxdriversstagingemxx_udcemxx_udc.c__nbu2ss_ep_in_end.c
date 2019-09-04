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
struct nbu2ss_udc {struct fc_regs* p_regs; } ;
struct fc_regs {TYPE_1__* EP_REGS; int /*<<< orphan*/  EP0_CONTROL; int /*<<< orphan*/  EP0_WRITE; } ;
struct TYPE_2__ {int /*<<< orphan*/  EP_CONTROL; int /*<<< orphan*/  EP_WRITE; } ;

/* Variables and functions */
 int EP0_AUTO ; 
 int EP0_DEND ; 
 int EP0_DW ; 
 int EPN_AUTO ; 
 int EPN_DEND ; 
 int EPN_DW ; 
 int /*<<< orphan*/  _nbu2ss_bitclr (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _nbu2ss_bitset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _nbu2ss_ep_in_end(
	struct nbu2ss_udc *udc,
	u32 epnum,
	u32 data32,
	u32 length
)
{
	u32		data;
	u32		num;
	struct fc_regs	*preg = udc->p_regs;

	if (length >= sizeof(u32))
		return;

	if (epnum == 0) {
		_nbu2ss_bitclr(&preg->EP0_CONTROL, EP0_AUTO);

		/* Writing of 1-4 bytes */
		if (length)
			_nbu2ss_writel(&preg->EP0_WRITE, data32);

		data = ((length << 5) & EP0_DW) | EP0_DEND;
		_nbu2ss_writel(&preg->EP0_CONTROL, data);

		_nbu2ss_bitset(&preg->EP0_CONTROL, EP0_AUTO);
	} else {
		num = epnum - 1;

		_nbu2ss_bitclr(&preg->EP_REGS[num].EP_CONTROL, EPN_AUTO);

		/* Writing of 1-4 bytes */
		if (length)
			_nbu2ss_writel(&preg->EP_REGS[num].EP_WRITE, data32);

		data = (((length) << 5) & EPN_DW) | EPN_DEND;
		_nbu2ss_bitset(&preg->EP_REGS[num].EP_CONTROL, data);

		_nbu2ss_bitset(&preg->EP_REGS[num].EP_CONTROL, EPN_AUTO);
	}
}
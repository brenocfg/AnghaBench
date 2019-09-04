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
typedef  int /*<<< orphan*/  u32 ;
struct nbu2ss_udc {TYPE_1__* p_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  EP0_CONTROL; } ;

/* Variables and functions */
 scalar_t__ EP0_ONAK ; 
 int /*<<< orphan*/  EP0_PIDCLR ; 
 int /*<<< orphan*/  _nbu2ss_readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int EP0_receive_NULL(struct nbu2ss_udc *udc, bool pid_flag)
{
	u32		data;

	data = _nbu2ss_readl(&udc->p_regs->EP0_CONTROL);
	data &= ~(u32)EP0_ONAK;

	if (pid_flag)
		data |= EP0_PIDCLR;

	_nbu2ss_writel(&udc->p_regs->EP0_CONTROL, data);

	return 0;
}
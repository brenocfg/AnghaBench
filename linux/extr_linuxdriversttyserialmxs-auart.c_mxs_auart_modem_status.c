#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  dsr; int /*<<< orphan*/  rng; } ;
struct TYPE_9__ {TYPE_3__* state; TYPE_1__ icount; } ;
struct mxs_auart_port {int mctrl_prev; TYPE_4__ port; scalar_t__ ms_irq_enabled; } ;
struct TYPE_7__ {int /*<<< orphan*/  delta_msr_wait; } ;
struct TYPE_8__ {TYPE_2__ port; } ;

/* Variables and functions */
 int MCTRL_ANY_DELTA ; 
 int TIOCM_CD ; 
 int TIOCM_CTS ; 
 int TIOCM_DSR ; 
 int TIOCM_RI ; 
 int /*<<< orphan*/  uart_handle_cts_change (TYPE_4__*,int) ; 
 int /*<<< orphan*/  uart_handle_dcd_change (TYPE_4__*,int) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 mxs_auart_modem_status(struct mxs_auart_port *s, u32 mctrl)
{
	u32 mctrl_diff;

	mctrl_diff = mctrl ^ s->mctrl_prev;
	s->mctrl_prev = mctrl;
	if (mctrl_diff & MCTRL_ANY_DELTA && s->ms_irq_enabled &&
						s->port.state != NULL) {
		if (mctrl_diff & TIOCM_RI)
			s->port.icount.rng++;
		if (mctrl_diff & TIOCM_DSR)
			s->port.icount.dsr++;
		if (mctrl_diff & TIOCM_CD)
			uart_handle_dcd_change(&s->port, mctrl & TIOCM_CD);
		if (mctrl_diff & TIOCM_CTS)
			uart_handle_cts_change(&s->port, mctrl & TIOCM_CTS);

		wake_up_interruptible(&s->port.state->port.delta_msr_wait);
	}
	return mctrl;
}
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
struct zs_scc {int /*<<< orphan*/  zlock; } ;
struct uart_icount {int /*<<< orphan*/  overrun; int /*<<< orphan*/  parity; int /*<<< orphan*/  frame; int /*<<< orphan*/  brk; int /*<<< orphan*/  rx; } ;
struct uart_port {unsigned int read_status_mask; TYPE_1__* state; struct uart_icount icount; } ;
struct zs_port {unsigned int tty_break; struct zs_scc* scc; struct uart_port port; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_RES ; 
 unsigned int FRM_ERR ; 
 unsigned int PAR_ERR ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
 unsigned int Rx_BRK ; 
 unsigned int Rx_CH_AV ; 
 unsigned int Rx_OVR ; 
 unsigned int Rx_SYS ; 
 unsigned int TTY_BREAK ; 
 unsigned int TTY_FRAME ; 
 unsigned int TTY_NORMAL ; 
 unsigned int TTY_PARITY ; 
 unsigned int read_zsdata (struct zs_port*) ; 
 unsigned int read_zsreg (struct zs_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 scalar_t__ uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 
 int /*<<< orphan*/  uart_insert_char (struct uart_port*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 scalar_t__ unlikely (unsigned int) ; 
 int /*<<< orphan*/  write_zsreg (struct zs_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zs_receive_chars(struct zs_port *zport)
{
	struct uart_port *uport = &zport->port;
	struct zs_scc *scc = zport->scc;
	struct uart_icount *icount;
	unsigned int avail, status, ch, flag;
	int count;

	for (count = 16; count; count--) {
		spin_lock(&scc->zlock);
		avail = read_zsreg(zport, R0) & Rx_CH_AV;
		spin_unlock(&scc->zlock);
		if (!avail)
			break;

		spin_lock(&scc->zlock);
		status = read_zsreg(zport, R1) & (Rx_OVR | FRM_ERR | PAR_ERR);
		ch = read_zsdata(zport);
		spin_unlock(&scc->zlock);

		flag = TTY_NORMAL;

		icount = &uport->icount;
		icount->rx++;

		/* Handle the null char got when BREAK is removed.  */
		if (!ch)
			status |= zport->tty_break;
		if (unlikely(status &
			     (Rx_OVR | FRM_ERR | PAR_ERR | Rx_SYS | Rx_BRK))) {
			zport->tty_break = 0;

			/* Reset the error indication.  */
			if (status & (Rx_OVR | FRM_ERR | PAR_ERR)) {
				spin_lock(&scc->zlock);
				write_zsreg(zport, R0, ERR_RES);
				spin_unlock(&scc->zlock);
			}

			if (status & (Rx_SYS | Rx_BRK)) {
				icount->brk++;
				/* SysRq discards the null char.  */
				if (status & Rx_SYS)
					continue;
			} else if (status & FRM_ERR)
				icount->frame++;
			else if (status & PAR_ERR)
				icount->parity++;
			if (status & Rx_OVR)
				icount->overrun++;

			status &= uport->read_status_mask;
			if (status & Rx_BRK)
				flag = TTY_BREAK;
			else if (status & FRM_ERR)
				flag = TTY_FRAME;
			else if (status & PAR_ERR)
				flag = TTY_PARITY;
		}

		if (uart_handle_sysrq_char(uport, ch))
			continue;

		uart_insert_char(uport, status, Rx_OVR, ch, flag);
	}

	tty_flip_buffer_push(&uport->state->port);
}
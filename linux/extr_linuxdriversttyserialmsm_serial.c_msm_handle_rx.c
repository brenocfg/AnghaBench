#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rx; int /*<<< orphan*/  frame; int /*<<< orphan*/  brk; int /*<<< orphan*/  overrun; } ;
struct uart_port {unsigned int read_status_mask; int /*<<< orphan*/  lock; TYPE_2__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 char TTY_BREAK ; 
 char TTY_FRAME ; 
 char TTY_NORMAL ; 
 char TTY_OVERRUN ; 
 int /*<<< orphan*/  UART_CR ; 
 int /*<<< orphan*/  UART_CR_CMD_RESET_ERR ; 
 int /*<<< orphan*/  UART_RF ; 
 int /*<<< orphan*/  UART_SR ; 
 int UART_SR_OVERRUN ; 
 unsigned int UART_SR_PAR_FRAME_ERR ; 
 unsigned int UART_SR_RX_BREAK ; 
 unsigned int UART_SR_RX_READY ; 
 int msm_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,unsigned int,char) ; 
 scalar_t__ uart_handle_break (struct uart_port*) ; 
 int uart_handle_sysrq_char (struct uart_port*,unsigned int) ; 

__attribute__((used)) static void msm_handle_rx(struct uart_port *port)
{
	struct tty_port *tport = &port->state->port;
	unsigned int sr;

	/*
	 * Handle overrun. My understanding of the hardware is that overrun
	 * is not tied to the RX buffer, so we handle the case out of band.
	 */
	if ((msm_read(port, UART_SR) & UART_SR_OVERRUN)) {
		port->icount.overrun++;
		tty_insert_flip_char(tport, 0, TTY_OVERRUN);
		msm_write(port, UART_CR_CMD_RESET_ERR, UART_CR);
	}

	/* and now the main RX loop */
	while ((sr = msm_read(port, UART_SR)) & UART_SR_RX_READY) {
		unsigned int c;
		char flag = TTY_NORMAL;
		int sysrq;

		c = msm_read(port, UART_RF);

		if (sr & UART_SR_RX_BREAK) {
			port->icount.brk++;
			if (uart_handle_break(port))
				continue;
		} else if (sr & UART_SR_PAR_FRAME_ERR) {
			port->icount.frame++;
		} else {
			port->icount.rx++;
		}

		/* Mask conditions we're ignorning. */
		sr &= port->read_status_mask;

		if (sr & UART_SR_RX_BREAK)
			flag = TTY_BREAK;
		else if (sr & UART_SR_PAR_FRAME_ERR)
			flag = TTY_FRAME;

		spin_unlock(&port->lock);
		sysrq = uart_handle_sysrq_char(port, c);
		spin_lock(&port->lock);
		if (!sysrq)
			tty_insert_flip_char(tport, c, flag);
	}

	spin_unlock(&port->lock);
	tty_flip_buffer_push(tport);
	spin_lock(&port->lock);
}
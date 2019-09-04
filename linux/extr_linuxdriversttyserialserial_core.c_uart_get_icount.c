#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct uart_state {int dummy; } ;
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  icount; } ;
struct uart_icount {int /*<<< orphan*/  buf_overrun; int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;
struct tty_struct {struct uart_state* driver_data; } ;
struct serial_icounter_struct {int /*<<< orphan*/  buf_overrun; int /*<<< orphan*/  brk; int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  dsr; int /*<<< orphan*/  cts; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  memcpy (struct uart_icount*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_port_deref (struct uart_port*) ; 
 struct uart_port* uart_port_ref (struct uart_state*) ; 

__attribute__((used)) static int uart_get_icount(struct tty_struct *tty,
			  struct serial_icounter_struct *icount)
{
	struct uart_state *state = tty->driver_data;
	struct uart_icount cnow;
	struct uart_port *uport;

	uport = uart_port_ref(state);
	if (!uport)
		return -EIO;
	spin_lock_irq(&uport->lock);
	memcpy(&cnow, &uport->icount, sizeof(struct uart_icount));
	spin_unlock_irq(&uport->lock);
	uart_port_deref(uport);

	icount->cts         = cnow.cts;
	icount->dsr         = cnow.dsr;
	icount->rng         = cnow.rng;
	icount->dcd         = cnow.dcd;
	icount->rx          = cnow.rx;
	icount->tx          = cnow.tx;
	icount->frame       = cnow.frame;
	icount->overrun     = cnow.overrun;
	icount->parity      = cnow.parity;
	icount->brk         = cnow.brk;
	icount->buf_overrun = cnow.buf_overrun;

	return 0;
}
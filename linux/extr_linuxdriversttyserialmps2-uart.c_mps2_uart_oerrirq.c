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
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  overrun; } ;
struct uart_port {int /*<<< orphan*/  lock; TYPE_2__ icount; TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  TTY_OVERRUN ; 
 int /*<<< orphan*/  UARTn_INT ; 
 int UARTn_INT_RX_OVERRUN ; 
 int UARTn_INT_TX_OVERRUN ; 
 int mps2_uart_read8 (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mps2_uart_write8 (struct uart_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_port*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mps2_uart_oerrirq(int irq, void *data)
{
	irqreturn_t handled = IRQ_NONE;
	struct uart_port *port = data;
	u8 irqflag = mps2_uart_read8(port, UARTn_INT);

	spin_lock(&port->lock);

	if (irqflag & UARTn_INT_RX_OVERRUN) {
		struct tty_port *tport = &port->state->port;

		mps2_uart_write8(port, UARTn_INT_RX_OVERRUN, UARTn_INT);
		port->icount.overrun++;
		tty_insert_flip_char(tport, 0, TTY_OVERRUN);
		tty_flip_buffer_push(tport);
		handled = IRQ_HANDLED;
	}

	/*
	 * It's never been seen in practice and it never *should* happen since
	 * we check if there is enough room in TX buffer before sending data.
	 * So we keep this check in case something suspicious has happened.
	 */
	if (irqflag & UARTn_INT_TX_OVERRUN) {
		mps2_uart_write8(port, UARTn_INT_TX_OVERRUN, UARTn_INT);
		handled = IRQ_HANDLED;
	}

	spin_unlock(&port->lock);

	return handled;
}
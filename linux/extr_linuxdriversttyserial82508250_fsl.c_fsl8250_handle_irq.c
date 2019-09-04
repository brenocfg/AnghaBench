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
struct uart_port {unsigned int (* serial_in ) (struct uart_port*,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {unsigned char (* serial_in ) (TYPE_1__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  lock; } ;
struct uart_8250_port {unsigned char lsr_saved_flags; TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_IIR ; 
 unsigned int UART_IIR_NO_INT ; 
 int /*<<< orphan*/  UART_LSR ; 
 unsigned char UART_LSR_BI ; 
 unsigned char UART_LSR_DR ; 
 unsigned char UART_LSR_THRE ; 
 int /*<<< orphan*/  UART_RX ; 
 int /*<<< orphan*/  serial8250_modem_status (struct uart_8250_port*) ; 
 unsigned char serial8250_rx_chars (struct uart_8250_port*,unsigned char) ; 
 int /*<<< orphan*/  serial8250_tx_chars (struct uart_8250_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int stub1 (struct uart_port*,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (struct uart_port*,int /*<<< orphan*/ ) ; 
 unsigned char stub3 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (unsigned char) ; 
 struct uart_8250_port* up_to_u8250p (struct uart_port*) ; 

int fsl8250_handle_irq(struct uart_port *port)
{
	unsigned char lsr, orig_lsr;
	unsigned long flags;
	unsigned int iir;
	struct uart_8250_port *up = up_to_u8250p(port);

	spin_lock_irqsave(&up->port.lock, flags);

	iir = port->serial_in(port, UART_IIR);
	if (iir & UART_IIR_NO_INT) {
		spin_unlock_irqrestore(&up->port.lock, flags);
		return 0;
	}

	/* This is the WAR; if last event was BRK, then read and return */
	if (unlikely(up->lsr_saved_flags & UART_LSR_BI)) {
		up->lsr_saved_flags &= ~UART_LSR_BI;
		port->serial_in(port, UART_RX);
		spin_unlock_irqrestore(&up->port.lock, flags);
		return 1;
	}

	lsr = orig_lsr = up->port.serial_in(&up->port, UART_LSR);

	if (lsr & (UART_LSR_DR | UART_LSR_BI))
		lsr = serial8250_rx_chars(up, lsr);

	serial8250_modem_status(up);

	if (lsr & UART_LSR_THRE)
		serial8250_tx_chars(up);

	up->lsr_saved_flags = orig_lsr;
	spin_unlock_irqrestore(&up->port.lock, flags);
	return 1;
}
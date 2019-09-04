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
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__* state; } ;
struct uart_sunsu_port {TYPE_2__ port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  UART_IIR ; 
 int UART_IIR_NO_INT ; 
 int /*<<< orphan*/  UART_LSR ; 
 unsigned char UART_LSR_DR ; 
 unsigned char UART_LSR_THRE ; 
 int /*<<< orphan*/  check_modem_status (struct uart_sunsu_port*) ; 
 int /*<<< orphan*/  receive_chars (struct uart_sunsu_port*,unsigned char*) ; 
 int serial_in (struct uart_sunsu_port*,int /*<<< orphan*/ ) ; 
 unsigned char serial_inp (struct uart_sunsu_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transmit_chars (struct uart_sunsu_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t sunsu_serial_interrupt(int irq, void *dev_id)
{
	struct uart_sunsu_port *up = dev_id;
	unsigned long flags;
	unsigned char status;

	spin_lock_irqsave(&up->port.lock, flags);

	do {
		status = serial_inp(up, UART_LSR);
		if (status & UART_LSR_DR)
			receive_chars(up, &status);
		check_modem_status(up);
		if (status & UART_LSR_THRE)
			transmit_chars(up);

		spin_unlock_irqrestore(&up->port.lock, flags);

		tty_flip_buffer_push(&up->port.state->port);

		spin_lock_irqsave(&up->port.lock, flags);

	} while (!(serial_in(up, UART_IIR) & UART_IIR_NO_INT));

	spin_unlock_irqrestore(&up->port.lock, flags);

	return IRQ_HANDLED;
}
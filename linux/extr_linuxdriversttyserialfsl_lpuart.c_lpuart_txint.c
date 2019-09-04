#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lock; scalar_t__ membase; scalar_t__ x_char; TYPE_1__* state; } ;
struct lpuart_port {TYPE_2__ port; } ;
struct circ_buf {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {struct circ_buf xmit; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  UARTDATA ; 
 scalar_t__ UARTDR ; 
 scalar_t__ WAKEUP_CHARS ; 
 int /*<<< orphan*/  lpuart32_stop_tx (TYPE_2__*) ; 
 int /*<<< orphan*/  lpuart32_transmit_buffer (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart32_write (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ lpuart_is_32 (struct lpuart_port*) ; 
 int /*<<< orphan*/  lpuart_stop_tx (TYPE_2__*) ; 
 int /*<<< orphan*/  lpuart_transmit_buffer (struct lpuart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ uart_circ_chars_pending (struct circ_buf*) ; 
 scalar_t__ uart_circ_empty (struct circ_buf*) ; 
 scalar_t__ uart_tx_stopped (TYPE_2__*) ; 
 int /*<<< orphan*/  uart_write_wakeup (TYPE_2__*) ; 
 int /*<<< orphan*/  writeb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static irqreturn_t lpuart_txint(int irq, void *dev_id)
{
	struct lpuart_port *sport = dev_id;
	struct circ_buf *xmit = &sport->port.state->xmit;
	unsigned long flags;

	spin_lock_irqsave(&sport->port.lock, flags);
	if (sport->port.x_char) {
		if (lpuart_is_32(sport))
			lpuart32_write(&sport->port, sport->port.x_char, UARTDATA);
		else
			writeb(sport->port.x_char, sport->port.membase + UARTDR);
		goto out;
	}

	if (uart_circ_empty(xmit) || uart_tx_stopped(&sport->port)) {
		if (lpuart_is_32(sport))
			lpuart32_stop_tx(&sport->port);
		else
			lpuart_stop_tx(&sport->port);
		goto out;
	}

	if (lpuart_is_32(sport))
		lpuart32_transmit_buffer(sport);
	else
		lpuart_transmit_buffer(sport);

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(&sport->port);

out:
	spin_unlock_irqrestore(&sport->port.lock, flags);
	return IRQ_HANDLED;
}
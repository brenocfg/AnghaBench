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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct rp2_uart_port {TYPE_1__ port; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ RP2_TX_FIFO_COUNT ; 
 unsigned int TIOCSER_TEMT ; 
 struct rp2_uart_port* port_to_up (struct uart_port*) ; 
 unsigned long readw (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int rp2_uart_tx_empty(struct uart_port *port)
{
	struct rp2_uart_port *up = port_to_up(port);
	unsigned long tx_fifo_bytes, flags;

	/*
	 * This should probably check the transmitter, not the FIFO.
	 * But the TXEMPTY bit doesn't seem to work unless the TX IRQ is
	 * enabled.
	 */
	spin_lock_irqsave(&up->port.lock, flags);
	tx_fifo_bytes = readw(up->base + RP2_TX_FIFO_COUNT);
	spin_unlock_irqrestore(&up->port.lock, flags);

	return tx_fifo_bytes ? 0 : TIOCSER_TEMT;
}
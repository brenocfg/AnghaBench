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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct ar933x_uart_port {TYPE_1__ port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int AR933X_UART_CS_HOST_INT ; 
 int /*<<< orphan*/  AR933X_UART_CS_REG ; 
 int /*<<< orphan*/  AR933X_UART_INT_EN_REG ; 
 int /*<<< orphan*/  AR933X_UART_INT_REG ; 
 unsigned int AR933X_UART_INT_RX_VALID ; 
 unsigned int AR933X_UART_INT_TX_EMPTY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned int ar933x_uart_read (struct ar933x_uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar933x_uart_rx_chars (struct ar933x_uart_port*) ; 
 int /*<<< orphan*/  ar933x_uart_stop_tx_interrupt (struct ar933x_uart_port*) ; 
 int /*<<< orphan*/  ar933x_uart_tx_chars (struct ar933x_uart_port*) ; 
 int /*<<< orphan*/  ar933x_uart_write (struct ar933x_uart_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t ar933x_uart_interrupt(int irq, void *dev_id)
{
	struct ar933x_uart_port *up = dev_id;
	unsigned int status;

	status = ar933x_uart_read(up, AR933X_UART_CS_REG);
	if ((status & AR933X_UART_CS_HOST_INT) == 0)
		return IRQ_NONE;

	spin_lock(&up->port.lock);

	status = ar933x_uart_read(up, AR933X_UART_INT_REG);
	status &= ar933x_uart_read(up, AR933X_UART_INT_EN_REG);

	if (status & AR933X_UART_INT_RX_VALID) {
		ar933x_uart_write(up, AR933X_UART_INT_REG,
				  AR933X_UART_INT_RX_VALID);
		ar933x_uart_rx_chars(up);
	}

	if (status & AR933X_UART_INT_TX_EMPTY) {
		ar933x_uart_write(up, AR933X_UART_INT_REG,
				  AR933X_UART_INT_TX_EMPTY);
		ar933x_uart_stop_tx_interrupt(up);
		ar933x_uart_tx_chars(up);
	}

	spin_unlock(&up->port.lock);

	return IRQ_HANDLED;
}
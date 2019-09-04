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
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq; int /*<<< orphan*/  cons; } ;

/* Variables and functions */
 int /*<<< orphan*/  console_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  qcom_geni_serial_stop_rx (struct uart_port*) ; 
 int /*<<< orphan*/  qcom_geni_serial_stop_tx (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ uart_console (struct uart_port*) ; 

__attribute__((used)) static void qcom_geni_serial_shutdown(struct uart_port *uport)
{
	unsigned long flags;

	/* Stop the console before stopping the current tx */
	if (uart_console(uport))
		console_stop(uport->cons);

	free_irq(uport->irq, uport);
	spin_lock_irqsave(&uport->lock, flags);
	qcom_geni_serial_stop_tx(uport);
	qcom_geni_serial_stop_rx(uport);
	spin_unlock_irqrestore(&uport->lock, flags);
}
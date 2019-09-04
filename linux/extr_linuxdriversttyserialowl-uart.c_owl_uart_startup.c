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
typedef  int u32 ;
struct uart_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_TRIGGER_HIGH ; 
 int /*<<< orphan*/  OWL_UART_CTL ; 
 int OWL_UART_CTL_EN ; 
 int OWL_UART_CTL_RXIE ; 
 int OWL_UART_CTL_TXIE ; 
 int /*<<< orphan*/  OWL_UART_STAT ; 
 int OWL_UART_STAT_RIP ; 
 int OWL_UART_STAT_RXER ; 
 int OWL_UART_STAT_RXST ; 
 int OWL_UART_STAT_TFER ; 
 int OWL_UART_STAT_TIP ; 
 int /*<<< orphan*/  owl_uart_irq ; 
 int owl_uart_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  owl_uart_write (struct uart_port*,int,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int owl_uart_startup(struct uart_port *port)
{
	u32 val;
	unsigned long flags;
	int ret;

	ret = request_irq(port->irq, owl_uart_irq, IRQF_TRIGGER_HIGH,
			"owl-uart", port);
	if (ret)
		return ret;

	spin_lock_irqsave(&port->lock, flags);

	val = owl_uart_read(port, OWL_UART_STAT);
	val |= OWL_UART_STAT_RIP | OWL_UART_STAT_TIP
		| OWL_UART_STAT_RXER | OWL_UART_STAT_TFER | OWL_UART_STAT_RXST;
	owl_uart_write(port, val, OWL_UART_STAT);

	val = owl_uart_read(port, OWL_UART_CTL);
	val |= OWL_UART_CTL_RXIE | OWL_UART_CTL_TXIE;
	val |= OWL_UART_CTL_EN;
	owl_uart_write(port, val, OWL_UART_CTL);

	spin_unlock_irqrestore(&port->lock, flags);

	return 0;
}
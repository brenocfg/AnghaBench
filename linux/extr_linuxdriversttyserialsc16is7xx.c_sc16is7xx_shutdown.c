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
struct uart_port {int /*<<< orphan*/  dev; } ;
struct sc16is7xx_port {int /*<<< orphan*/  kworker; } ;

/* Variables and functions */
 int /*<<< orphan*/  SC16IS7XX_EFCR_REG ; 
 int SC16IS7XX_EFCR_RXDISABLE_BIT ; 
 int SC16IS7XX_EFCR_TXDISABLE_BIT ; 
 int /*<<< orphan*/  SC16IS7XX_IER_REG ; 
 struct sc16is7xx_port* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_flush_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sc16is7xx_port_update (struct uart_port*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sc16is7xx_port_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc16is7xx_power (struct uart_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sc16is7xx_shutdown(struct uart_port *port)
{
	struct sc16is7xx_port *s = dev_get_drvdata(port->dev);

	/* Disable all interrupts */
	sc16is7xx_port_write(port, SC16IS7XX_IER_REG, 0);
	/* Disable TX/RX */
	sc16is7xx_port_update(port, SC16IS7XX_EFCR_REG,
			      SC16IS7XX_EFCR_RXDISABLE_BIT |
			      SC16IS7XX_EFCR_TXDISABLE_BIT,
			      SC16IS7XX_EFCR_RXDISABLE_BIT |
			      SC16IS7XX_EFCR_TXDISABLE_BIT);

	sc16is7xx_power(port, 0);

	kthread_flush_worker(&s->kworker);
}
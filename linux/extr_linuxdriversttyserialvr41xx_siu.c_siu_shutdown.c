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
typedef  int /*<<< orphan*/  uint8_t ;
struct uart_port {scalar_t__ type; int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; int /*<<< orphan*/  mctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSIUINT_ALL ; 
 scalar_t__ PORT_VR41XX_DSIU ; 
 int /*<<< orphan*/  TIOCM_OUT2 ; 
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_LCR ; 
 int /*<<< orphan*/  UART_LCR_SBC ; 
 int /*<<< orphan*/  UART_RX ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_port*) ; 
 int /*<<< orphan*/  siu_clear_fifo (struct uart_port*) ; 
 int /*<<< orphan*/  siu_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siu_set_mctrl (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siu_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vr41xx_disable_dsiuint (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void siu_shutdown(struct uart_port *port)
{
	unsigned long flags;
	uint8_t lcr;

	siu_write(port, UART_IER, 0);

	spin_lock_irqsave(&port->lock, flags);

	port->mctrl &= ~TIOCM_OUT2;
	siu_set_mctrl(port, port->mctrl);

	spin_unlock_irqrestore(&port->lock, flags);

	lcr = siu_read(port, UART_LCR);
	lcr &= ~UART_LCR_SBC;
	siu_write(port, UART_LCR, lcr);

	siu_clear_fifo(port);

	(void)siu_read(port, UART_RX);

	if (port->type == PORT_VR41XX_DSIU)
		vr41xx_disable_dsiuint(DSIUINT_ALL);

	free_irq(port->irq, port);
}
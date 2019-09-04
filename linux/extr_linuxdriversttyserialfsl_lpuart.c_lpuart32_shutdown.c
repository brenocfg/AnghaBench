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
struct uart_port {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  UARTCTRL ; 
 unsigned long UARTCTRL_RE ; 
 unsigned long UARTCTRL_RIE ; 
 unsigned long UARTCTRL_TCIE ; 
 unsigned long UARTCTRL_TE ; 
 unsigned long UARTCTRL_TIE ; 
 unsigned long lpuart32_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpuart32_write (struct uart_port*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void lpuart32_shutdown(struct uart_port *port)
{
	unsigned long temp;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);

	/* disable Rx/Tx and interrupts */
	temp = lpuart32_read(port, UARTCTRL);
	temp &= ~(UARTCTRL_TE | UARTCTRL_RE |
			UARTCTRL_TIE | UARTCTRL_TCIE | UARTCTRL_RIE);
	lpuart32_write(port, temp, UARTCTRL);

	spin_unlock_irqrestore(&port->lock, flags);
}
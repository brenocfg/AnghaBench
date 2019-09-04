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
 int /*<<< orphan*/  RP2_TXRX_CTL ; 
 int /*<<< orphan*/  RP2_TXRX_CTL_BREAK_m ; 
 int /*<<< orphan*/  port_to_up (struct uart_port*) ; 
 int /*<<< orphan*/  rp2_rmw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rp2_uart_break_ctl(struct uart_port *port, int break_state)
{
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	rp2_rmw(port_to_up(port), RP2_TXRX_CTL, RP2_TXRX_CTL_BREAK_m,
		break_state ? RP2_TXRX_CTL_BREAK_m : 0);
	spin_unlock_irqrestore(&port->lock, flags);
}
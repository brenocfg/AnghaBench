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
struct uart_ip22zilog_port {int dummy; } ;

/* Variables and functions */
 struct uart_ip22zilog_port* UART_ZILOG (struct uart_port*) ; 
 scalar_t__ ZS_IS_CONS (struct uart_ip22zilog_port*) ; 
 int /*<<< orphan*/  __ip22zilog_startup (struct uart_ip22zilog_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ip22zilog_startup(struct uart_port *port)
{
	struct uart_ip22zilog_port *up = UART_ZILOG(port);
	unsigned long flags;

	if (ZS_IS_CONS(up))
		return 0;

	spin_lock_irqsave(&port->lock, flags);
	__ip22zilog_startup(up);
	spin_unlock_irqrestore(&port->lock, flags);
	return 0;
}
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
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transmit_chars (struct uart_port*) ; 

__attribute__((used)) static void ioc4_cb_output_lowat(struct uart_port *the_port)
{
	unsigned long pflags;

	/* ip_lock is set on the call here */
	if (the_port) {
		spin_lock_irqsave(&the_port->lock, pflags);
		transmit_chars(the_port);
		spin_unlock_irqrestore(&the_port->lock, pflags);
	}
}
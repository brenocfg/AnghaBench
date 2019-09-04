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
struct ioc3_port {struct uart_port* ip_port; struct ioc3_card* ip_card; } ;
struct ioc3_card {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NOT_PROGRESS () ; 
 struct ioc3_port* get_ioc3_port (struct uart_port*) ; 
 int ic3_startup_local (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ic3_startup(struct uart_port *the_port)
{
	int retval;
	struct ioc3_port *port;
	struct ioc3_card *card_ptr;
	unsigned long port_flags;

	if (!the_port) {
		NOT_PROGRESS();
		return -ENODEV;
	}
	port = get_ioc3_port(the_port);
	if (!port) {
		NOT_PROGRESS();
		return -ENODEV;
	}
	card_ptr = port->ip_card;
	port->ip_port = the_port;

	if (!card_ptr) {
		NOT_PROGRESS();
		return -ENODEV;
	}

	/* Start up the serial port */
	spin_lock_irqsave(&the_port->lock, port_flags);
	retval = ic3_startup_local(the_port);
	spin_unlock_irqrestore(&the_port->lock, port_flags);
	return retval;
}
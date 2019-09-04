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
struct ioc3_port {TYPE_1__* ip_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transmit_chars (TYPE_1__*) ; 

__attribute__((used)) static void ioc3_cb_output_lowat(struct ioc3_port *port)
{
	unsigned long pflags;

	/* the_port->lock is set on the call here */
	if (port->ip_port) {
		spin_lock_irqsave(&port->ip_port->lock, pflags);
		transmit_chars(port->ip_port);
		spin_unlock_irqrestore(&port->ip_port->lock, pflags);
	}
}
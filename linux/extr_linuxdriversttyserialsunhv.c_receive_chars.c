#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {TYPE_1__* state; } ;
struct tty_port {int dummy; } ;
struct TYPE_4__ {scalar_t__ (* receive_chars ) (struct uart_port*) ;} ;
struct TYPE_3__ {struct tty_port port; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct uart_port*) ; 
 int /*<<< orphan*/  sun_do_break () ; 
 TYPE_2__* sunhv_ops ; 

__attribute__((used)) static struct tty_port *receive_chars(struct uart_port *port)
{
	struct tty_port *tport = NULL;

	if (port->state != NULL)		/* Unopened serial console */
		tport = &port->state->port;

	if (sunhv_ops->receive_chars(port))
		sun_do_break();

	return tport;
}
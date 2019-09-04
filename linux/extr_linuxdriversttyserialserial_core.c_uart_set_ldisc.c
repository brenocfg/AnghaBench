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
struct TYPE_3__ {int /*<<< orphan*/  mutex; } ;
struct uart_state {TYPE_1__ port; } ;
struct uart_port {TYPE_2__* ops; } ;
struct tty_struct {int /*<<< orphan*/  termios; struct uart_state* driver_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_ldisc ) (struct uart_port*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_port*,int /*<<< orphan*/ *) ; 
 struct uart_port* uart_port_check (struct uart_state*) ; 

__attribute__((used)) static void uart_set_ldisc(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;
	struct uart_port *uport;

	mutex_lock(&state->port.mutex);
	uport = uart_port_check(state);
	if (uport && uport->ops->set_ldisc)
		uport->ops->set_ldisc(uport, &tty->termios);
	mutex_unlock(&state->port.mutex);
}
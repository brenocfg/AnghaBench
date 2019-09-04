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
struct uart_state {int /*<<< orphan*/  port; } ;
struct uart_driver {struct uart_state* state; } ;
struct tty_struct {int index; struct uart_state* driver_data; TYPE_1__* driver; } ;
struct file {int dummy; } ;
struct TYPE_2__ {struct uart_driver* driver_state; } ;

/* Variables and functions */
 int tty_port_open (int /*<<< orphan*/ *,struct tty_struct*,struct file*) ; 

__attribute__((used)) static int uart_open(struct tty_struct *tty, struct file *filp)
{
	struct uart_driver *drv = tty->driver->driver_state;
	int retval, line = tty->index;
	struct uart_state *state = drv->state + line;

	tty->driver_data = state;

	retval = tty_port_open(&state->port, tty, filp);
	if (retval > 0)
		retval = 0;

	return retval;
}
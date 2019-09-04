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
struct tty_struct {int /*<<< orphan*/  flags; } ;
struct tty_port {int /*<<< orphan*/  console; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_port_close_end (struct tty_port*,struct tty_struct*) ; 
 scalar_t__ tty_port_close_start (struct tty_port*,struct tty_struct*,struct file*) ; 
 int /*<<< orphan*/  tty_port_shutdown (struct tty_port*,struct tty_struct*) ; 
 int /*<<< orphan*/  tty_port_tty_set (struct tty_port*,int /*<<< orphan*/ *) ; 

void tty_port_close(struct tty_port *port, struct tty_struct *tty,
							struct file *filp)
{
	if (tty_port_close_start(port, tty, filp) == 0)
		return;
	tty_port_shutdown(port, tty);
	if (!port->console)
		set_bit(TTY_IO_ERROR, &tty->flags);
	tty_port_close_end(port, tty);
	tty_port_tty_set(port, NULL);
}
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
struct tty_struct {scalar_t__ hw_stopped; struct cyclades_port* driver_data; } ;
struct ktermios {int c_cflag; } ;
struct cyclades_port {int dummy; } ;

/* Variables and functions */
 int CRTSCTS ; 
 int /*<<< orphan*/  C_CRTSCTS (struct tty_struct*) ; 
 int /*<<< orphan*/  cy_set_line_char (struct cyclades_port*,struct tty_struct*) ; 
 int /*<<< orphan*/  cy_start (struct tty_struct*) ; 

__attribute__((used)) static void cy_set_termios(struct tty_struct *tty, struct ktermios *old_termios)
{
	struct cyclades_port *info = tty->driver_data;

#ifdef CY_DEBUG_OTHER
	printk(KERN_DEBUG "cyc:cy_set_termios ttyC%d\n", info->line);
#endif

	cy_set_line_char(info, tty);

	if ((old_termios->c_cflag & CRTSCTS) && !C_CRTSCTS(tty)) {
		tty->hw_stopped = 0;
		cy_start(tty);
	}
#if 0
	/*
	 * No need to wake up processes in open wait, since they
	 * sample the CLOCAL flag once, and don't recheck it.
	 * XXX  It's not clear whether the current behavior is correct
	 * or not.  Hence, this may change.....
	 */
	if (!(old_termios->c_cflag & CLOCAL) && C_CLOCAL(tty))
		wake_up_interruptible(&info->port.open_wait);
#endif
}
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
struct ktermios {int /*<<< orphan*/  c_ospeed; int /*<<< orphan*/  c_ispeed; int /*<<< orphan*/  c_line; } ;
struct tty_struct {int index; struct ktermios termios; TYPE_1__* driver; } ;
struct TYPE_2__ {int flags; struct ktermios init_termios; struct ktermios** termios; } ;

/* Variables and functions */
 int TTY_DRIVER_RESET_TERMIOS ; 
 int /*<<< orphan*/  tty_termios_baud_rate (struct ktermios*) ; 
 int /*<<< orphan*/  tty_termios_input_baud_rate (struct ktermios*) ; 

void tty_init_termios(struct tty_struct *tty)
{
	struct ktermios *tp;
	int idx = tty->index;

	if (tty->driver->flags & TTY_DRIVER_RESET_TERMIOS)
		tty->termios = tty->driver->init_termios;
	else {
		/* Check for lazy saved data */
		tp = tty->driver->termios[idx];
		if (tp != NULL) {
			tty->termios = *tp;
			tty->termios.c_line  = tty->driver->init_termios.c_line;
		} else
			tty->termios = tty->driver->init_termios;
	}
	/* Compatibility until drivers always set this */
	tty->termios.c_ispeed = tty_termios_input_baud_rate(&tty->termios);
	tty->termios.c_ospeed = tty_termios_baud_rate(&tty->termios);
}
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
struct ktermios {int dummy; } ;
struct tty_struct {int index; struct ktermios termios; TYPE_1__* driver; } ;
struct TYPE_2__ {int flags; struct ktermios** termios; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TTY_DRIVER_RESET_TERMIOS ; 
 struct ktermios* kmalloc (int,int /*<<< orphan*/ ) ; 

void tty_save_termios(struct tty_struct *tty)
{
	struct ktermios *tp;
	int idx = tty->index;

	/* If the port is going to reset then it has no termios to save */
	if (tty->driver->flags & TTY_DRIVER_RESET_TERMIOS)
		return;

	/* Stash the termios data */
	tp = tty->driver->termios[idx];
	if (tp == NULL) {
		tp = kmalloc(sizeof(struct ktermios), GFP_KERNEL);
		if (tp == NULL)
			return;
		tty->driver->termios[idx] = tp;
	}
	*tp = tty->termios;
}
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
struct ktermios {int c_cflag; } ;
struct tty_struct {int /*<<< orphan*/  termios_rwsem; TYPE_1__* ops; struct ktermios termios; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_termios ) (struct tty_struct*,struct ktermios*) ;} ;

/* Variables and functions */
 int CLOCAL ; 
 int C_CLOCAL (struct tty_struct*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct tty_struct*,struct ktermios*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tty_change_softcar(struct tty_struct *tty, int arg)
{
	int ret = 0;
	int bit = arg ? CLOCAL : 0;
	struct ktermios old;

	down_write(&tty->termios_rwsem);
	old = tty->termios;
	tty->termios.c_cflag &= ~CLOCAL;
	tty->termios.c_cflag |= bit;
	if (tty->ops->set_termios)
		tty->ops->set_termios(tty, &old);
	if (C_CLOCAL(tty) != bit)
		ret = -EINVAL;
	up_write(&tty->termios_rwsem);
	return ret;
}
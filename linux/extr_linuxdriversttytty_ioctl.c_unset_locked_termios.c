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
struct ktermios {int c_iflag; int c_oflag; int c_cflag; int c_lflag; scalar_t__* c_cc; scalar_t__ c_line; } ;
struct tty_struct {struct ktermios termios_locked; struct ktermios termios; } ;

/* Variables and functions */
 int NCCS ; 

__attribute__((used)) static void unset_locked_termios(struct tty_struct *tty, struct ktermios *old)
{
	struct ktermios *termios = &tty->termios;
	struct ktermios *locked  = &tty->termios_locked;
	int	i;

#define NOSET_MASK(x, y, z) (x = ((x) & ~(z)) | ((y) & (z)))

	NOSET_MASK(termios->c_iflag, old->c_iflag, locked->c_iflag);
	NOSET_MASK(termios->c_oflag, old->c_oflag, locked->c_oflag);
	NOSET_MASK(termios->c_cflag, old->c_cflag, locked->c_cflag);
	NOSET_MASK(termios->c_lflag, old->c_lflag, locked->c_lflag);
	termios->c_line = locked->c_line ? old->c_line : termios->c_line;
	for (i = 0; i < NCCS; i++)
		termios->c_cc[i] = locked->c_cc[i] ?
			old->c_cc[i] : termios->c_cc[i];
	/* FIXME: What should we do for i/ospeed */
}
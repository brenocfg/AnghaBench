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
struct termios {int dummy; } ;
struct termio {int /*<<< orphan*/  sg_kill; int /*<<< orphan*/  sg_erase; int /*<<< orphan*/ * c_cc; } ;
struct sgttyb {int /*<<< orphan*/  sg_kill; int /*<<< orphan*/  sg_erase; int /*<<< orphan*/ * c_cc; } ;
typedef  int /*<<< orphan*/  char_u ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NUL ; 
 int /*<<< orphan*/  TCGETA ; 
 int /*<<< orphan*/  TIOCGETP ; 
 size_t VERASE ; 
 size_t VINTR ; 
 int /*<<< orphan*/  add_termcode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_fixdel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_termcode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intr_char ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termio*) ; 
 int /*<<< orphan*/  read_cmd_fd ; 
 int tcgetattr (int /*<<< orphan*/ ,struct termio*) ; 

void
get_stty()
{
    char_u  buf[2];
    char_u  *p;

    /* Why is NeXT excluded here (and not in os_unixx.h)? */
#if defined(ECHOE) && defined(ICANON) && (defined(HAVE_TERMIO_H) || defined(HAVE_TERMIOS_H)) && !defined(__NeXT__)
    /* for "new" tty systems */
# ifdef HAVE_TERMIOS_H
    struct termios keys;
# else
    struct termio keys;
# endif

# if defined(HAVE_TERMIOS_H)
    if (tcgetattr(read_cmd_fd, &keys) != -1)
# else
    if (ioctl(read_cmd_fd, TCGETA, &keys) != -1)
# endif
    {
	buf[0] = keys.c_cc[VERASE];
	intr_char = keys.c_cc[VINTR];
#else
    /* for "old" tty systems */
    struct sgttyb keys;

    if (ioctl(read_cmd_fd, TIOCGETP, &keys) != -1)
    {
	buf[0] = keys.sg_erase;
	intr_char = keys.sg_kill;
#endif
	buf[1] = NUL;
	add_termcode((char_u *)"kb", buf, FALSE);

	/*
	 * If <BS> and <DEL> are now the same, redefine <DEL>.
	 */
	p = find_termcode((char_u *)"kD");
	if (p != NULL && p[0] == buf[0] && p[1] == buf[1])
	    do_fixdel(NULL);
    }
#if 0
    }	    /* to keep cindent happy */
#endif
}
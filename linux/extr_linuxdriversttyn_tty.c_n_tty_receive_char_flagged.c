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
struct tty_struct {int dummy; } ;

/* Variables and functions */
#define  TTY_BREAK 131 
#define  TTY_FRAME 130 
#define  TTY_OVERRUN 129 
#define  TTY_PARITY 128 
 int /*<<< orphan*/  n_tty_receive_break (struct tty_struct*) ; 
 int /*<<< orphan*/  n_tty_receive_overrun (struct tty_struct*) ; 
 int /*<<< orphan*/  n_tty_receive_parity_error (struct tty_struct*,unsigned char) ; 
 int /*<<< orphan*/  tty_err (struct tty_struct*,char*,char) ; 

__attribute__((used)) static void
n_tty_receive_char_flagged(struct tty_struct *tty, unsigned char c, char flag)
{
	switch (flag) {
	case TTY_BREAK:
		n_tty_receive_break(tty);
		break;
	case TTY_PARITY:
	case TTY_FRAME:
		n_tty_receive_parity_error(tty, c);
		break;
	case TTY_OVERRUN:
		n_tty_receive_overrun(tty);
		break;
	default:
		tty_err(tty, "unknown flag %d\n", flag);
		break;
	}
}
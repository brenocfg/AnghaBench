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
struct tty_struct {int /*<<< orphan*/  read_wait; int /*<<< orphan*/  fasync; int /*<<< orphan*/  flow_stopped; scalar_t__ stopped; struct n_tty_data* disc_data; } ;
struct n_tty_data {int lnext; size_t canon_head; size_t read_head; int /*<<< orphan*/  read_flags; scalar_t__ icanon; } ;

/* Variables and functions */
 unsigned char EOF_CHAR (struct tty_struct*) ; 
 unsigned char EOL2_CHAR (struct tty_struct*) ; 
 unsigned char EOL_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  EPOLLIN ; 
 unsigned char ERASE_CHAR (struct tty_struct*) ; 
 unsigned char INTR_CHAR (struct tty_struct*) ; 
 scalar_t__ I_ICRNL (struct tty_struct*) ; 
 scalar_t__ I_IGNCR (struct tty_struct*) ; 
 scalar_t__ I_INLCR (struct tty_struct*) ; 
 scalar_t__ I_IXANY (struct tty_struct*) ; 
 scalar_t__ I_IXON (struct tty_struct*) ; 
 scalar_t__ I_PARMRK (struct tty_struct*) ; 
 unsigned char KILL_CHAR (struct tty_struct*) ; 
 unsigned char LNEXT_CHAR (struct tty_struct*) ; 
 scalar_t__ L_ECHO (struct tty_struct*) ; 
 scalar_t__ L_ECHOCTL (struct tty_struct*) ; 
 scalar_t__ L_ECHONL (struct tty_struct*) ; 
 scalar_t__ L_IEXTEN (struct tty_struct*) ; 
 scalar_t__ L_ISIG (struct tty_struct*) ; 
 scalar_t__ MASK (size_t) ; 
 int N_TTY_BUF_SIZE ; 
 int /*<<< orphan*/  POLL_IN ; 
 unsigned char QUIT_CHAR (struct tty_struct*) ; 
 unsigned char REPRINT_CHAR (struct tty_struct*) ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIGTSTP ; 
 unsigned char START_CHAR (struct tty_struct*) ; 
 unsigned char STOP_CHAR (struct tty_struct*) ; 
 unsigned char SUSP_CHAR (struct tty_struct*) ; 
 unsigned char WERASE_CHAR (struct tty_struct*) ; 
 unsigned char __DISABLED_CHAR ; 
 int /*<<< orphan*/  commit_echoes (struct tty_struct*) ; 
 int /*<<< orphan*/  echo_char (unsigned char,struct tty_struct*) ; 
 int /*<<< orphan*/  echo_char_raw (char,struct n_tty_data*) ; 
 int /*<<< orphan*/  echo_set_canon_col (struct n_tty_data*) ; 
 int /*<<< orphan*/  eraser (unsigned char,struct tty_struct*) ; 
 int /*<<< orphan*/  finish_erasing (struct n_tty_data*) ; 
 int /*<<< orphan*/  kill_fasync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  n_tty_receive_signal_char (struct tty_struct*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  process_echoes (struct tty_struct*) ; 
 int /*<<< orphan*/  put_tty_queue (unsigned char,struct n_tty_data*) ; 
 unsigned char read_buf (struct n_tty_data*,size_t) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_store_release (scalar_t__*,int) ; 
 int /*<<< orphan*/  start_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  stop_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  wake_up_interruptible_poll (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
n_tty_receive_char_special(struct tty_struct *tty, unsigned char c)
{
	struct n_tty_data *ldata = tty->disc_data;

	if (I_IXON(tty)) {
		if (c == START_CHAR(tty)) {
			start_tty(tty);
			process_echoes(tty);
			return 0;
		}
		if (c == STOP_CHAR(tty)) {
			stop_tty(tty);
			return 0;
		}
	}

	if (L_ISIG(tty)) {
		if (c == INTR_CHAR(tty)) {
			n_tty_receive_signal_char(tty, SIGINT, c);
			return 0;
		} else if (c == QUIT_CHAR(tty)) {
			n_tty_receive_signal_char(tty, SIGQUIT, c);
			return 0;
		} else if (c == SUSP_CHAR(tty)) {
			n_tty_receive_signal_char(tty, SIGTSTP, c);
			return 0;
		}
	}

	if (tty->stopped && !tty->flow_stopped && I_IXON(tty) && I_IXANY(tty)) {
		start_tty(tty);
		process_echoes(tty);
	}

	if (c == '\r') {
		if (I_IGNCR(tty))
			return 0;
		if (I_ICRNL(tty))
			c = '\n';
	} else if (c == '\n' && I_INLCR(tty))
		c = '\r';

	if (ldata->icanon) {
		if (c == ERASE_CHAR(tty) || c == KILL_CHAR(tty) ||
		    (c == WERASE_CHAR(tty) && L_IEXTEN(tty))) {
			eraser(c, tty);
			commit_echoes(tty);
			return 0;
		}
		if (c == LNEXT_CHAR(tty) && L_IEXTEN(tty)) {
			ldata->lnext = 1;
			if (L_ECHO(tty)) {
				finish_erasing(ldata);
				if (L_ECHOCTL(tty)) {
					echo_char_raw('^', ldata);
					echo_char_raw('\b', ldata);
					commit_echoes(tty);
				}
			}
			return 1;
		}
		if (c == REPRINT_CHAR(tty) && L_ECHO(tty) && L_IEXTEN(tty)) {
			size_t tail = ldata->canon_head;

			finish_erasing(ldata);
			echo_char(c, tty);
			echo_char_raw('\n', ldata);
			while (MASK(tail) != MASK(ldata->read_head)) {
				echo_char(read_buf(ldata, tail), tty);
				tail++;
			}
			commit_echoes(tty);
			return 0;
		}
		if (c == '\n') {
			if (L_ECHO(tty) || L_ECHONL(tty)) {
				echo_char_raw('\n', ldata);
				commit_echoes(tty);
			}
			goto handle_newline;
		}
		if (c == EOF_CHAR(tty)) {
			c = __DISABLED_CHAR;
			goto handle_newline;
		}
		if ((c == EOL_CHAR(tty)) ||
		    (c == EOL2_CHAR(tty) && L_IEXTEN(tty))) {
			/*
			 * XXX are EOL_CHAR and EOL2_CHAR echoed?!?
			 */
			if (L_ECHO(tty)) {
				/* Record the column of first canon char. */
				if (ldata->canon_head == ldata->read_head)
					echo_set_canon_col(ldata);
				echo_char(c, tty);
				commit_echoes(tty);
			}
			/*
			 * XXX does PARMRK doubling happen for
			 * EOL_CHAR and EOL2_CHAR?
			 */
			if (c == (unsigned char) '\377' && I_PARMRK(tty))
				put_tty_queue(c, ldata);

handle_newline:
			set_bit(ldata->read_head & (N_TTY_BUF_SIZE - 1), ldata->read_flags);
			put_tty_queue(c, ldata);
			smp_store_release(&ldata->canon_head, ldata->read_head);
			kill_fasync(&tty->fasync, SIGIO, POLL_IN);
			wake_up_interruptible_poll(&tty->read_wait, EPOLLIN);
			return 0;
		}
	}

	if (L_ECHO(tty)) {
		finish_erasing(ldata);
		if (c == '\n')
			echo_char_raw('\n', ldata);
		else {
			/* Record the column of first canon char. */
			if (ldata->canon_head == ldata->read_head)
				echo_set_canon_col(ldata);
			echo_char(c, tty);
		}
		commit_echoes(tty);
	}

	/* PARMRK doubling check */
	if (c == (unsigned char) '\377' && I_PARMRK(tty))
		put_tty_queue(c, ldata);

	put_tty_queue(c, ldata);
	return 0;
}
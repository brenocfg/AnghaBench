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
struct tty_struct {int /*<<< orphan*/  stopped; } ;
struct TYPE_2__ {int cols; int /*<<< orphan*/  lock; } ;
struct tty3270 {scalar_t__ esc_state; int cx; int cy; TYPE_1__ view; int /*<<< orphan*/  timer; int /*<<< orphan*/  wcc; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  TW_PLUSALARM ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty3270_convert_line (struct tty3270*,int) ; 
 int /*<<< orphan*/  tty3270_cr (struct tty3270*) ; 
 int /*<<< orphan*/  tty3270_erase_display (struct tty3270*,int) ; 
 int /*<<< orphan*/  tty3270_escape_sequence (struct tty3270*,unsigned char const) ; 
 int /*<<< orphan*/  tty3270_lf (struct tty3270*) ; 
 int /*<<< orphan*/  tty3270_put_character (struct tty3270*,unsigned char const) ; 
 int /*<<< orphan*/  tty3270_set_timer (struct tty3270*,int) ; 

__attribute__((used)) static void
tty3270_do_write(struct tty3270 *tp, struct tty_struct *tty,
		const unsigned char *buf, int count)
{
	int i_msg, i;

	spin_lock_bh(&tp->view.lock);
	for (i_msg = 0; !tty->stopped && i_msg < count; i_msg++) {
		if (tp->esc_state != 0) {
			/* Continue escape sequence. */
			tty3270_escape_sequence(tp, buf[i_msg]);
			continue;
		}

		switch (buf[i_msg]) {
		case 0x07:		/* '\a' -- Alarm */
			tp->wcc |= TW_PLUSALARM;
			break;
		case 0x08:		/* Backspace. */
			if (tp->cx > 0) {
				tp->cx--;
				tty3270_put_character(tp, ' ');
			}
			break;
		case 0x09:		/* '\t' -- Tabulate */
			for (i = tp->cx % 8; i < 8; i++) {
				if (tp->cx >= tp->view.cols) {
					tty3270_cr(tp);
					tty3270_lf(tp);
					break;
				}
				tty3270_put_character(tp, ' ');
				tp->cx++;
			}
			break;
		case 0x0a:		/* '\n' -- New Line */
			tty3270_cr(tp);
			tty3270_lf(tp);
			break;
		case 0x0c:		/* '\f' -- Form Feed */
			tty3270_erase_display(tp, 2);
			tp->cx = tp->cy = 0;
			break;
		case 0x0d:		/* '\r' -- Carriage Return */
			tp->cx = 0;
			break;
		case 0x0f:		/* SuSE "exit alternate mode" */
			break;
		case 0x1b:		/* Start escape sequence. */
			tty3270_escape_sequence(tp, buf[i_msg]);
			break;
		default:		/* Insert normal character. */
			if (tp->cx >= tp->view.cols) {
				tty3270_cr(tp);
				tty3270_lf(tp);
			}
			tty3270_put_character(tp, buf[i_msg]);
			tp->cx++;
			break;
		}
	}
	/* Convert current line to 3270 data fragment. */
	tty3270_convert_line(tp, tp->cy);

	/* Setup timer to update display after 1/10 second */
	if (!timer_pending(&tp->timer))
		tty3270_set_timer(tp, HZ/10);

	spin_unlock_bh(&tp->view.lock);
}
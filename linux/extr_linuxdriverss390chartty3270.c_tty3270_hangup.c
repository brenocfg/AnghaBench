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
struct tty_struct {struct tty3270* driver_data; } ;
struct TYPE_2__ {int rows; int /*<<< orphan*/  lock; } ;
struct tty3270 {int nr_lines; TYPE_1__ view; int /*<<< orphan*/  update_flags; int /*<<< orphan*/  saved_f_color; int /*<<< orphan*/  f_color; int /*<<< orphan*/  saved_highlight; int /*<<< orphan*/  highlight; scalar_t__ saved_cy; scalar_t__ cy; scalar_t__ saved_cx; scalar_t__ cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAC_RESET ; 
 int /*<<< orphan*/  TAX_RESET ; 
 int /*<<< orphan*/  TTY_UPDATE_ALL ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty3270_blank_line (struct tty3270*) ; 
 int /*<<< orphan*/  tty3270_blank_screen (struct tty3270*) ; 
 int /*<<< orphan*/  tty3270_set_timer (struct tty3270*,int) ; 

__attribute__((used)) static void
tty3270_hangup(struct tty_struct *tty)
{
	struct tty3270 *tp;

	tp = tty->driver_data;
	if (!tp)
		return;
	spin_lock_bh(&tp->view.lock);
	tp->cx = tp->saved_cx = 0;
	tp->cy = tp->saved_cy = 0;
	tp->highlight = tp->saved_highlight = TAX_RESET;
	tp->f_color = tp->saved_f_color = TAC_RESET;
	tty3270_blank_screen(tp);
	while (tp->nr_lines < tp->view.rows - 2)
		tty3270_blank_line(tp);
	tp->update_flags = TTY_UPDATE_ALL;
	spin_unlock_bh(&tp->view.lock);
	tty3270_set_timer(tp, 1);
}
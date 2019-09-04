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
struct tty3270_line {scalar_t__ len; } ;
struct TYPE_2__ {int rows; } ;
struct tty3270 {int cy; TYPE_1__ view; struct tty3270_line* screen; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty3270_blank_line (struct tty3270*) ; 
 int /*<<< orphan*/  tty3270_convert_line (struct tty3270*,int) ; 
 int /*<<< orphan*/  tty3270_rebuild_update (struct tty3270*) ; 

__attribute__((used)) static void
tty3270_lf(struct tty3270 *tp)
{
	struct tty3270_line temp;
	int i;

	tty3270_convert_line(tp, tp->cy);
	if (tp->cy < tp->view.rows - 3) {
		tp->cy++;
		return;
	}
	/* Last line just filled up. Add new, blank line. */
	tty3270_blank_line(tp);
	temp = tp->screen[0];
	temp.len = 0;
	for (i = 0; i < tp->view.rows - 3; i++)
		tp->screen[i] = tp->screen[i+1];
	tp->screen[tp->view.rows - 3] = temp;
	tty3270_rebuild_update(tp);
}
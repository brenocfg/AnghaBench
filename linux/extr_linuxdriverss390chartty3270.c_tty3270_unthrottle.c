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
struct tty_struct {struct tty3270* driver_data; } ;
struct tty3270 {scalar_t__ attn; scalar_t__ throttle; } ;

/* Variables and functions */
 int /*<<< orphan*/  tty3270_issue_read (struct tty3270*,int) ; 

__attribute__((used)) static void
tty3270_unthrottle(struct tty_struct * tty)
{
	struct tty3270 *tp;

	tp = tty->driver_data;
	if (!tp)
		return;
	tp->throttle = 0;
	if (tp->attn)
		tty3270_issue_read(tp, 1);
}
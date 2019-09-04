#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {TYPE_2__* ops; int /*<<< orphan*/  flags; TYPE_1__* link; scalar_t__ packet; int /*<<< orphan*/  port; int /*<<< orphan*/  write_wait; int /*<<< orphan*/  read_wait; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;
struct TYPE_4__ {scalar_t__ write; } ;
struct TYPE_3__ {scalar_t__ ctrl_status; } ;

/* Variables and functions */
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLPRI ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 int /*<<< orphan*/  TTY_OTHER_CLOSED ; 
 scalar_t__ WAKEUP_CHARS ; 
 scalar_t__ input_available_p (struct tty_struct*,int) ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_buffer_flush_work (int /*<<< orphan*/ ) ; 
 scalar_t__ tty_chars_in_buffer (struct tty_struct*) ; 
 scalar_t__ tty_hung_up_p (struct file*) ; 
 int /*<<< orphan*/  tty_is_writelocked (struct tty_struct*) ; 
 scalar_t__ tty_write_room (struct tty_struct*) ; 

__attribute__((used)) static __poll_t n_tty_poll(struct tty_struct *tty, struct file *file,
							poll_table *wait)
{
	__poll_t mask = 0;

	poll_wait(file, &tty->read_wait, wait);
	poll_wait(file, &tty->write_wait, wait);
	if (input_available_p(tty, 1))
		mask |= EPOLLIN | EPOLLRDNORM;
	else {
		tty_buffer_flush_work(tty->port);
		if (input_available_p(tty, 1))
			mask |= EPOLLIN | EPOLLRDNORM;
	}
	if (tty->packet && tty->link->ctrl_status)
		mask |= EPOLLPRI | EPOLLIN | EPOLLRDNORM;
	if (test_bit(TTY_OTHER_CLOSED, &tty->flags))
		mask |= EPOLLHUP;
	if (tty_hung_up_p(file))
		mask |= EPOLLHUP;
	if (tty->ops->write && !tty_is_writelocked(tty) &&
			tty_chars_in_buffer(tty) < WAKEUP_CHARS &&
			tty_write_room(tty) > 0)
		mask |= EPOLLOUT | EPOLLWRNORM;
	return mask;
}
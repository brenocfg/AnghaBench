#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {scalar_t__ session; } ;
struct file {int f_mode; } ;
struct TYPE_5__ {TYPE_1__* signal; } ;
struct TYPE_4__ {scalar_t__ tty; scalar_t__ leader; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EPERM ; 
 int FMODE_READ ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  proc_set_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  session_clear_tty (scalar_t__) ; 
 scalar_t__ task_session (TYPE_2__*) ; 
 int /*<<< orphan*/  tasklist_lock ; 
 int /*<<< orphan*/  tty_lock (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty_struct*) ; 

__attribute__((used)) static int tiocsctty(struct tty_struct *tty, struct file *file, int arg)
{
	int ret = 0;

	tty_lock(tty);
	read_lock(&tasklist_lock);

	if (current->signal->leader && (task_session(current) == tty->session))
		goto unlock;

	/*
	 * The process must be a session leader and
	 * not have a controlling tty already.
	 */
	if (!current->signal->leader || current->signal->tty) {
		ret = -EPERM;
		goto unlock;
	}

	if (tty->session) {
		/*
		 * This tty is already the controlling
		 * tty for another session group!
		 */
		if (arg == 1 && capable(CAP_SYS_ADMIN)) {
			/*
			 * Steal it away
			 */
			session_clear_tty(tty->session);
		} else {
			ret = -EPERM;
			goto unlock;
		}
	}

	/* See the comment in tty_open_proc_set_tty(). */
	if ((file->f_mode & FMODE_READ) == 0 && !capable(CAP_SYS_ADMIN)) {
		ret = -EPERM;
		goto unlock;
	}

	proc_set_tty(tty);
unlock:
	read_unlock(&tasklist_lock);
	tty_unlock(tty);
	return ret;
}
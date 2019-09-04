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
struct tty_struct {int /*<<< orphan*/  ctrl_lock; struct pid* pgrp; int /*<<< orphan*/  fasync; } ;
struct pid {int dummy; } ;
struct file {int dummy; } ;
typedef  enum pid_type { ____Placeholder_pid_type } pid_type ;

/* Variables and functions */
 int PIDTYPE_PGID ; 
 int PIDTYPE_TGID ; 
 int /*<<< orphan*/  __f_setown (struct file*,struct pid*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int fasync_helper (int,struct file*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 struct tty_struct* file_tty (struct file*) ; 
 int /*<<< orphan*/  get_pid (struct pid*) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pid* task_pid (int /*<<< orphan*/ ) ; 
 scalar_t__ tty_paranoia_check (struct tty_struct*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int __tty_fasync(int fd, struct file *filp, int on)
{
	struct tty_struct *tty = file_tty(filp);
	unsigned long flags;
	int retval = 0;

	if (tty_paranoia_check(tty, file_inode(filp), "tty_fasync"))
		goto out;

	retval = fasync_helper(fd, filp, on, &tty->fasync);
	if (retval <= 0)
		goto out;

	if (on) {
		enum pid_type type;
		struct pid *pid;

		spin_lock_irqsave(&tty->ctrl_lock, flags);
		if (tty->pgrp) {
			pid = tty->pgrp;
			type = PIDTYPE_PGID;
		} else {
			pid = task_pid(current);
			type = PIDTYPE_TGID;
		}
		get_pid(pid);
		spin_unlock_irqrestore(&tty->ctrl_lock, flags);
		__f_setown(filp, pid, type, 0);
		put_pid(pid);
		retval = 0;
	}
out:
	return retval;
}
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
struct pid {int dummy; } ;
struct file {int dummy; } ;
struct autofs_sb_info {int flags; int pipefd; int /*<<< orphan*/  wq_mutex; struct file* pipe; struct pid* oz_pgrp; } ;
struct TYPE_2__ {int pipefd; } ;
struct autofs_dev_ioctl {TYPE_1__ setpipefd; } ;

/* Variables and functions */
 int AUTOFS_SBI_CATATONIC ; 
 int EBADF ; 
 int EBUSY ; 
 int EINVAL ; 
 int EPIPE ; 
 int /*<<< orphan*/  PIDTYPE_PGID ; 
 scalar_t__ autofs_prepare_pipe (struct file*) ; 
 int /*<<< orphan*/  current ; 
 struct file* fget (int) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct pid* get_task_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ns_of_pid (struct pid*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  put_pid (struct pid*) ; 
 int /*<<< orphan*/  swap (struct pid*,struct pid*) ; 

__attribute__((used)) static int autofs_dev_ioctl_setpipefd(struct file *fp,
				      struct autofs_sb_info *sbi,
				      struct autofs_dev_ioctl *param)
{
	int pipefd;
	int err = 0;
	struct pid *new_pid = NULL;

	if (param->setpipefd.pipefd == -1)
		return -EINVAL;

	pipefd = param->setpipefd.pipefd;

	mutex_lock(&sbi->wq_mutex);
	if (!(sbi->flags & AUTOFS_SBI_CATATONIC)) {
		mutex_unlock(&sbi->wq_mutex);
		return -EBUSY;
	} else {
		struct file *pipe;

		new_pid = get_task_pid(current, PIDTYPE_PGID);

		if (ns_of_pid(new_pid) != ns_of_pid(sbi->oz_pgrp)) {
			pr_warn("not allowed to change PID namespace\n");
			err = -EINVAL;
			goto out;
		}

		pipe = fget(pipefd);
		if (!pipe) {
			err = -EBADF;
			goto out;
		}
		if (autofs_prepare_pipe(pipe) < 0) {
			err = -EPIPE;
			fput(pipe);
			goto out;
		}
		swap(sbi->oz_pgrp, new_pid);
		sbi->pipefd = pipefd;
		sbi->pipe = pipe;
		sbi->flags &= ~AUTOFS_SBI_CATATONIC;
	}
out:
	put_pid(new_pid);
	mutex_unlock(&sbi->wq_mutex);
	return err;
}
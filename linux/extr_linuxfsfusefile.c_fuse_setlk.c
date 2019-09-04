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
struct inode {int dummy; } ;
struct fuse_lk_in {int dummy; } ;
struct fuse_conn {int /*<<< orphan*/  pid_ns; } ;
struct file_lock {int fl_flags; scalar_t__ fl_type; TYPE_1__* fl_lmops; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_2__ {scalar_t__ lm_grant; } ;

/* Variables and functions */
 int EINTR ; 
 int ENOLCK ; 
 int ERESTARTSYS ; 
 int FL_CLOSE_POSIX ; 
 int FL_SLEEP ; 
 int /*<<< orphan*/  FUSE_ARGS (int /*<<< orphan*/ ) ; 
 int FUSE_SETLK ; 
 int FUSE_SETLKW ; 
 scalar_t__ F_UNLCK ; 
 int /*<<< orphan*/  args ; 
 int /*<<< orphan*/  current ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  fuse_lk_fill (int /*<<< orphan*/ *,struct file*,struct file_lock*,int,int /*<<< orphan*/ ,int,struct fuse_lk_in*) ; 
 int fuse_simple_request (struct fuse_conn*,int /*<<< orphan*/ *) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 int /*<<< orphan*/  pid_nr_ns (struct pid*,int /*<<< orphan*/ ) ; 
 struct pid* task_tgid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_setlk(struct file *file, struct file_lock *fl, int flock)
{
	struct inode *inode = file_inode(file);
	struct fuse_conn *fc = get_fuse_conn(inode);
	FUSE_ARGS(args);
	struct fuse_lk_in inarg;
	int opcode = (fl->fl_flags & FL_SLEEP) ? FUSE_SETLKW : FUSE_SETLK;
	struct pid *pid = fl->fl_type != F_UNLCK ? task_tgid(current) : NULL;
	pid_t pid_nr = pid_nr_ns(pid, fc->pid_ns);
	int err;

	if (fl->fl_lmops && fl->fl_lmops->lm_grant) {
		/* NLM needs asynchronous locks, which we don't support yet */
		return -ENOLCK;
	}

	/* Unlock on close is handled by the flush method */
	if ((fl->fl_flags & FL_CLOSE_POSIX) == FL_CLOSE_POSIX)
		return 0;

	fuse_lk_fill(&args, file, fl, opcode, pid_nr, flock, &inarg);
	err = fuse_simple_request(fc, &args);

	/* locking is restartable */
	if (err == -EINTR)
		err = -ERESTARTSYS;

	return err;
}
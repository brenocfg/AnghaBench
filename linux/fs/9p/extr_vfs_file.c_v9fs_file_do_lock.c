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
typedef  int uint8_t ;
struct v9fs_session_info {int /*<<< orphan*/  session_lock_timeout; } ;
struct p9_flock {scalar_t__ start; scalar_t__ length; scalar_t__ client_id; int /*<<< orphan*/  flags; int /*<<< orphan*/  proc_id; int /*<<< orphan*/  type; } ;
struct p9_fid {TYPE_1__* clnt; } ;
struct file_lock {int fl_flags; char fl_type; scalar_t__ fl_start; scalar_t__ fl_end; int /*<<< orphan*/  fl_pid; } ;
struct file {struct p9_fid* private_data; } ;
typedef  int /*<<< orphan*/  flock ;
struct TYPE_2__ {scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int ENOLCK ; 
 int FL_POSIX ; 
#define  F_RDLCK 134 
#define  F_UNLCK 133 
#define  F_WRLCK 132 
 scalar_t__ IS_SETLKW (int) ; 
 scalar_t__ OFFSET_MAX ; 
#define  P9_LOCK_BLOCKED 131 
#define  P9_LOCK_ERROR 130 
 int /*<<< orphan*/  P9_LOCK_FLAGS_BLOCK ; 
#define  P9_LOCK_GRACE 129 
#define  P9_LOCK_SUCCESS 128 
 int /*<<< orphan*/  P9_LOCK_TYPE_RDLCK ; 
 int /*<<< orphan*/  P9_LOCK_TYPE_UNLCK ; 
 int /*<<< orphan*/  P9_LOCK_TYPE_WRLCK ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int locks_lock_file_wait (struct file*,struct file_lock*) ; 
 int /*<<< orphan*/  memset (struct p9_flock*,int /*<<< orphan*/ ,int) ; 
 int p9_client_lock_dotl (struct p9_fid*,struct p9_flock*,int*) ; 
 scalar_t__ schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 struct v9fs_session_info* v9fs_inode2v9ses (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int v9fs_file_do_lock(struct file *filp, int cmd, struct file_lock *fl)
{
	struct p9_flock flock;
	struct p9_fid *fid;
	uint8_t status = P9_LOCK_ERROR;
	int res = 0;
	unsigned char fl_type;
	struct v9fs_session_info *v9ses;

	fid = filp->private_data;
	BUG_ON(fid == NULL);

	if ((fl->fl_flags & FL_POSIX) != FL_POSIX)
		BUG();

	res = locks_lock_file_wait(filp, fl);
	if (res < 0)
		goto out;

	/* convert posix lock to p9 tlock args */
	memset(&flock, 0, sizeof(flock));
	/* map the lock type */
	switch (fl->fl_type) {
	case F_RDLCK:
		flock.type = P9_LOCK_TYPE_RDLCK;
		break;
	case F_WRLCK:
		flock.type = P9_LOCK_TYPE_WRLCK;
		break;
	case F_UNLCK:
		flock.type = P9_LOCK_TYPE_UNLCK;
		break;
	}
	flock.start = fl->fl_start;
	if (fl->fl_end == OFFSET_MAX)
		flock.length = 0;
	else
		flock.length = fl->fl_end - fl->fl_start + 1;
	flock.proc_id = fl->fl_pid;
	flock.client_id = fid->clnt->name;
	if (IS_SETLKW(cmd))
		flock.flags = P9_LOCK_FLAGS_BLOCK;

	v9ses = v9fs_inode2v9ses(file_inode(filp));

	/*
	 * if its a blocked request and we get P9_LOCK_BLOCKED as the status
	 * for lock request, keep on trying
	 */
	for (;;) {
		res = p9_client_lock_dotl(fid, &flock, &status);
		if (res < 0)
			goto out_unlock;

		if (status != P9_LOCK_BLOCKED)
			break;
		if (status == P9_LOCK_BLOCKED && !IS_SETLKW(cmd))
			break;
		if (schedule_timeout_interruptible(v9ses->session_lock_timeout)
				!= 0)
			break;
		/*
		 * p9_client_lock_dotl overwrites flock.client_id with the
		 * server message, free and reuse the client name
		 */
		if (flock.client_id != fid->clnt->name) {
			kfree(flock.client_id);
			flock.client_id = fid->clnt->name;
		}
	}

	/* map 9p status to VFS status */
	switch (status) {
	case P9_LOCK_SUCCESS:
		res = 0;
		break;
	case P9_LOCK_BLOCKED:
		res = -EAGAIN;
		break;
	default:
		WARN_ONCE(1, "unknown lock status code: %d\n", status);
		/* fall through */
	case P9_LOCK_ERROR:
	case P9_LOCK_GRACE:
		res = -ENOLCK;
		break;
	}

out_unlock:
	/*
	 * incase server returned error for lock request, revert
	 * it locally
	 */
	if (res < 0 && fl->fl_type != F_UNLCK) {
		fl_type = fl->fl_type;
		fl->fl_type = F_UNLCK;
		/* Even if this fails we want to return the remote error */
		locks_lock_file_wait(filp, fl);
		fl->fl_type = fl_type;
	}
	if (flock.client_id != fid->clnt->name)
		kfree(flock.client_id);
out:
	return res;
}
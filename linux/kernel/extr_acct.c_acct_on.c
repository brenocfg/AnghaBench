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
struct TYPE_3__ {struct vfsmount* mnt; } ;
struct vfsmount {int f_mode; TYPE_1__ f_path; } ;
struct pid_namespace {int /*<<< orphan*/  bacct; } ;
struct fs_pin {int dummy; } ;
struct filename {int dummy; } ;
struct file {int f_mode; TYPE_1__ f_path; } ;
struct bsd_acct_struct {int /*<<< orphan*/  lock; int /*<<< orphan*/  pin; int /*<<< orphan*/  done; int /*<<< orphan*/  work; struct pid_namespace* ns; int /*<<< orphan*/  needcheck; struct vfsmount* file; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int EACCES ; 
 int EIO ; 
 int ENOMEM ; 
 int FMODE_CAN_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct vfsmount*) ; 
 int O_APPEND ; 
 int O_LARGEFILE ; 
 int O_WRONLY ; 
 int PTR_ERR (struct vfsmount*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mnt_drop_write (struct vfsmount*) ; 
 int __mnt_want_write (struct vfsmount*) ; 
 int /*<<< orphan*/  acct_pin_kill ; 
 int /*<<< orphan*/  atomic_long_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  close_work ; 
 int /*<<< orphan*/  current ; 
 TYPE_2__* file_inode (struct vfsmount*) ; 
 struct vfsmount* file_open_name (struct filename*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filp_close (struct vfsmount*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_fs_pin (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct bsd_acct_struct*) ; 
 struct bsd_acct_struct* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct vfsmount* mnt_clone_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pin_insert (int /*<<< orphan*/ *,struct vfsmount*) ; 
 int /*<<< orphan*/  pin_kill (struct fs_pin*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 struct pid_namespace* task_active_pid_ns (int /*<<< orphan*/ ) ; 
 struct fs_pin* xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acct_on(struct filename *pathname)
{
	struct file *file;
	struct vfsmount *mnt, *internal;
	struct pid_namespace *ns = task_active_pid_ns(current);
	struct bsd_acct_struct *acct;
	struct fs_pin *old;
	int err;

	acct = kzalloc(sizeof(struct bsd_acct_struct), GFP_KERNEL);
	if (!acct)
		return -ENOMEM;

	/* Difference from BSD - they don't do O_APPEND */
	file = file_open_name(pathname, O_WRONLY|O_APPEND|O_LARGEFILE, 0);
	if (IS_ERR(file)) {
		kfree(acct);
		return PTR_ERR(file);
	}

	if (!S_ISREG(file_inode(file)->i_mode)) {
		kfree(acct);
		filp_close(file, NULL);
		return -EACCES;
	}

	if (!(file->f_mode & FMODE_CAN_WRITE)) {
		kfree(acct);
		filp_close(file, NULL);
		return -EIO;
	}
	internal = mnt_clone_internal(&file->f_path);
	if (IS_ERR(internal)) {
		kfree(acct);
		filp_close(file, NULL);
		return PTR_ERR(internal);
	}
	err = __mnt_want_write(internal);
	if (err) {
		mntput(internal);
		kfree(acct);
		filp_close(file, NULL);
		return err;
	}
	mnt = file->f_path.mnt;
	file->f_path.mnt = internal;

	atomic_long_set(&acct->count, 1);
	init_fs_pin(&acct->pin, acct_pin_kill);
	acct->file = file;
	acct->needcheck = jiffies;
	acct->ns = ns;
	mutex_init(&acct->lock);
	INIT_WORK(&acct->work, close_work);
	init_completion(&acct->done);
	mutex_lock_nested(&acct->lock, 1);	/* nobody has seen it yet */
	pin_insert(&acct->pin, mnt);

	rcu_read_lock();
	old = xchg(&ns->bacct, &acct->pin);
	mutex_unlock(&acct->lock);
	pin_kill(old);
	__mnt_drop_write(mnt);
	mntput(mnt);
	return 0;
}
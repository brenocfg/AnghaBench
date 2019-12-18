#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vfsmount {int dummy; } ;
struct inode {int /*<<< orphan*/ * i_cdev; int /*<<< orphan*/  i_mode; } ;
struct TYPE_5__ {int /*<<< orphan*/  pid; } ;
struct TYPE_4__ {struct vfsmount* mnt; struct dentry* dentry; } ;
struct file {int f_mode; int f_flags; TYPE_2__ f_owner; TYPE_3__* f_op; struct inode* f_inode; TYPE_1__ f_path; } ;
struct dentry {int dummy; } ;
typedef  int fmode_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* release ) (struct inode*,struct file*) ;int /*<<< orphan*/  (* fasync ) (int,struct file*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int FASYNC ; 
 int FMODE_NEED_UNMOUNT ; 
 int FMODE_OPENED ; 
 int FMODE_PATH ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int FMODE_WRITER ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __mnt_drop_write (struct vfsmount*) ; 
 int /*<<< orphan*/  cdev_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dissolve_on_fput (struct vfsmount*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  eventpoll_release (struct file*) ; 
 int /*<<< orphan*/  file_free (struct file*) ; 
 int /*<<< orphan*/  fops_put (TYPE_3__*) ; 
 int /*<<< orphan*/  fsnotify_close (struct file*) ; 
 int /*<<< orphan*/  i_readcount_dec (struct inode*) ; 
 int /*<<< orphan*/  ima_file_free (struct file*) ; 
 int /*<<< orphan*/  locks_remove_file (struct file*) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  mntput (struct vfsmount*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_write_access (struct inode*) ; 
 int /*<<< orphan*/  stub1 (int,struct file*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct inode*,struct file*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void __fput(struct file *file)
{
	struct dentry *dentry = file->f_path.dentry;
	struct vfsmount *mnt = file->f_path.mnt;
	struct inode *inode = file->f_inode;
	fmode_t mode = file->f_mode;

	if (unlikely(!(file->f_mode & FMODE_OPENED)))
		goto out;

	might_sleep();

	fsnotify_close(file);
	/*
	 * The function eventpoll_release() should be the first called
	 * in the file cleanup chain.
	 */
	eventpoll_release(file);
	locks_remove_file(file);

	ima_file_free(file);
	if (unlikely(file->f_flags & FASYNC)) {
		if (file->f_op->fasync)
			file->f_op->fasync(-1, file, 0);
	}
	if (file->f_op->release)
		file->f_op->release(inode, file);
	if (unlikely(S_ISCHR(inode->i_mode) && inode->i_cdev != NULL &&
		     !(mode & FMODE_PATH))) {
		cdev_put(inode->i_cdev);
	}
	fops_put(file->f_op);
	put_pid(file->f_owner.pid);
	if ((mode & (FMODE_READ | FMODE_WRITE)) == FMODE_READ)
		i_readcount_dec(inode);
	if (mode & FMODE_WRITER) {
		put_write_access(inode);
		__mnt_drop_write(mnt);
	}
	dput(dentry);
	if (unlikely(mode & FMODE_NEED_UNMOUNT))
		dissolve_on_fput(mnt);
	mntput(mnt);
out:
	file_free(file);
}
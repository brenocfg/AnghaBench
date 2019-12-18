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
struct kiocb {int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct fd {int /*<<< orphan*/  file; } ;
struct cred {int dummy; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  fdput (struct fd) ; 
 int /*<<< orphan*/  file_end_write (int /*<<< orphan*/ ) ; 
 struct inode* file_inode (struct file*) ; 
 scalar_t__ file_remove_privs (struct file*) ; 
 int /*<<< orphan*/  file_start_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_lock (struct inode*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  ovl_copyattr (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ovl_inode_real (struct inode*) ; 
 int /*<<< orphan*/  ovl_iocb_to_rwf (struct kiocb*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_real_fdget (struct file*,struct fd*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 scalar_t__ vfs_iter_write (int /*<<< orphan*/ ,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ovl_write_iter(struct kiocb *iocb, struct iov_iter *iter)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file_inode(file);
	struct fd real;
	const struct cred *old_cred;
	ssize_t ret;

	if (!iov_iter_count(iter))
		return 0;

	inode_lock(inode);
	/* Update mode */
	ovl_copyattr(ovl_inode_real(inode), inode);
	ret = file_remove_privs(file);
	if (ret)
		goto out_unlock;

	ret = ovl_real_fdget(file, &real);
	if (ret)
		goto out_unlock;

	old_cred = ovl_override_creds(file_inode(file)->i_sb);
	file_start_write(real.file);
	ret = vfs_iter_write(real.file, iter, &iocb->ki_pos,
			     ovl_iocb_to_rwf(iocb));
	file_end_write(real.file);
	revert_creds(old_cred);

	/* Update size */
	ovl_copyattr(ovl_inode_real(inode), inode);

	fdput(real);

out_unlock:
	inode_unlock(inode);

	return ret;
}
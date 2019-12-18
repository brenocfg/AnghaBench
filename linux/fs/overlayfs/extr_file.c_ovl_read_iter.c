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
struct kiocb {int /*<<< orphan*/  ki_pos; struct file* ki_filp; } ;
struct iov_iter {int dummy; } ;
struct file {int dummy; } ;
struct fd {int /*<<< orphan*/  file; } ;
struct cred {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  fdput (struct fd) ; 
 TYPE_1__* file_inode (struct file*) ; 
 int /*<<< orphan*/  iov_iter_count (struct iov_iter*) ; 
 int /*<<< orphan*/  ovl_file_accessed (struct file*) ; 
 int /*<<< orphan*/  ovl_iocb_to_rwf (struct kiocb*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_real_fdget (struct file*,struct fd*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 scalar_t__ vfs_iter_read (int /*<<< orphan*/ ,struct iov_iter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t ovl_read_iter(struct kiocb *iocb, struct iov_iter *iter)
{
	struct file *file = iocb->ki_filp;
	struct fd real;
	const struct cred *old_cred;
	ssize_t ret;

	if (!iov_iter_count(iter))
		return 0;

	ret = ovl_real_fdget(file, &real);
	if (ret)
		return ret;

	old_cred = ovl_override_creds(file_inode(file)->i_sb);
	ret = vfs_iter_read(real.file, iter, &iocb->ki_pos,
			    ovl_iocb_to_rwf(iocb));
	revert_creds(old_cred);

	ovl_file_accessed(file);

	fdput(real);

	return ret;
}
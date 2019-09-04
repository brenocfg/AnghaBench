#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct file {int dummy; } ;
struct fd {struct file* file; } ;
struct cred {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  fdput (struct fd) ; 
 TYPE_1__* file_inode (struct file*) ; 
 scalar_t__ ovl_inode_upper (TYPE_1__*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 int ovl_real_fdget_meta (struct file*,struct fd*,int) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 int vfs_fsync_range (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ovl_fsync(struct file *file, loff_t start, loff_t end, int datasync)
{
	struct fd real;
	const struct cred *old_cred;
	int ret;

	ret = ovl_real_fdget_meta(file, &real, !datasync);
	if (ret)
		return ret;

	/* Don't sync lower file for fear of receiving EROFS error */
	if (file_inode(real.file) == ovl_inode_upper(file_inode(file))) {
		old_cred = ovl_override_creds(file_inode(file)->i_sb);
		ret = vfs_fsync_range(real.file, start, end, datasync);
		revert_creds(old_cred);
	}

	fdput(real);

	return ret;
}
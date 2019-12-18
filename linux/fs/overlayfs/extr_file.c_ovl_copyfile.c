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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {int dummy; } ;
struct fd {int /*<<< orphan*/  file; } ;
struct cred {int dummy; } ;
typedef  scalar_t__ loff_t ;
typedef  enum ovl_copyop { ____Placeholder_ovl_copyop } ovl_copyop ;

/* Variables and functions */
#define  OVL_CLONE 130 
#define  OVL_COPY 129 
#define  OVL_DEDUPE 128 
 int /*<<< orphan*/  fdput (struct fd) ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  ovl_copyattr (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  ovl_inode_real (struct inode*) ; 
 struct cred* ovl_override_creds (int /*<<< orphan*/ ) ; 
 scalar_t__ ovl_real_fdget (struct file*,struct fd*) ; 
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 
 scalar_t__ vfs_clone_file_range (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned int) ; 
 scalar_t__ vfs_copy_file_range (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned int) ; 
 scalar_t__ vfs_dedupe_file_range_one (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,unsigned int) ; 

__attribute__((used)) static loff_t ovl_copyfile(struct file *file_in, loff_t pos_in,
			    struct file *file_out, loff_t pos_out,
			    loff_t len, unsigned int flags, enum ovl_copyop op)
{
	struct inode *inode_out = file_inode(file_out);
	struct fd real_in, real_out;
	const struct cred *old_cred;
	loff_t ret;

	ret = ovl_real_fdget(file_out, &real_out);
	if (ret)
		return ret;

	ret = ovl_real_fdget(file_in, &real_in);
	if (ret) {
		fdput(real_out);
		return ret;
	}

	old_cred = ovl_override_creds(file_inode(file_out)->i_sb);
	switch (op) {
	case OVL_COPY:
		ret = vfs_copy_file_range(real_in.file, pos_in,
					  real_out.file, pos_out, len, flags);
		break;

	case OVL_CLONE:
		ret = vfs_clone_file_range(real_in.file, pos_in,
					   real_out.file, pos_out, len, flags);
		break;

	case OVL_DEDUPE:
		ret = vfs_dedupe_file_range_one(real_in.file, pos_in,
						real_out.file, pos_out, len,
						flags);
		break;
	}
	revert_creds(old_cred);

	/* Update size */
	ovl_copyattr(ovl_inode_real(inode_out), inode_out);

	fdput(real_in);
	fdput(real_out);

	return ret;
}
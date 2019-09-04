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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {scalar_t__ mnt; } ;
struct file {int f_mode; TYPE_2__* f_op; TYPE_1__ f_path; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_mode; } ;
struct TYPE_5__ {int (* dedupe_file_range ) (struct file*,int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int EISDIR ; 
 int EXDEV ; 
 int FMODE_WRITE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int clone_verify_area (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* file_inode (struct file*) ; 
 int /*<<< orphan*/  mnt_drop_write_file (struct file*) ; 
 int mnt_want_write_file (struct file*) ; 
 int stub1 (struct file*,int /*<<< orphan*/ ,struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vfs_dedupe_file_range_one(struct file *src_file, loff_t src_pos,
			      struct file *dst_file, loff_t dst_pos, u64 len)
{
	s64 ret;

	ret = mnt_want_write_file(dst_file);
	if (ret)
		return ret;

	ret = clone_verify_area(dst_file, dst_pos, len, true);
	if (ret < 0)
		goto out_drop_write;

	ret = -EINVAL;
	if (!(capable(CAP_SYS_ADMIN) || (dst_file->f_mode & FMODE_WRITE)))
		goto out_drop_write;

	ret = -EXDEV;
	if (src_file->f_path.mnt != dst_file->f_path.mnt)
		goto out_drop_write;

	ret = -EISDIR;
	if (S_ISDIR(file_inode(dst_file)->i_mode))
		goto out_drop_write;

	ret = -EINVAL;
	if (!dst_file->f_op->dedupe_file_range)
		goto out_drop_write;

	ret = dst_file->f_op->dedupe_file_range(src_file, src_pos,
						dst_file, dst_pos, len);
out_drop_write:
	mnt_drop_write_file(dst_file);

	return ret;
}
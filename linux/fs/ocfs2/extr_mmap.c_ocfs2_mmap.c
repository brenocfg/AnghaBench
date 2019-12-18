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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  mnt; } ;
struct file {TYPE_1__ f_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  file_inode (struct file*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_file_vm_ops ; 
 int ocfs2_inode_lock_atime (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ocfs2_inode_unlock (int /*<<< orphan*/ ,int) ; 

int ocfs2_mmap(struct file *file, struct vm_area_struct *vma)
{
	int ret = 0, lock_level = 0;

	ret = ocfs2_inode_lock_atime(file_inode(file),
				    file->f_path.mnt, &lock_level, 1);
	if (ret < 0) {
		mlog_errno(ret);
		goto out;
	}
	ocfs2_inode_unlock(file_inode(file), lock_level);
out:
	vma->vm_ops = &ocfs2_file_vm_ops;
	return 0;
}
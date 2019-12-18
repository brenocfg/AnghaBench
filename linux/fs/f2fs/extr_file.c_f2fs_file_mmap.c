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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; } ;
struct inode {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int f2fs_convert_inline_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_cp_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_file_vm_ops ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 struct inode* file_inode (struct file*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct inode *inode = file_inode(file);
	int err;

	if (unlikely(f2fs_cp_error(F2FS_I_SB(inode))))
		return -EIO;

	/* we don't need to use inline_data strictly */
	err = f2fs_convert_inline_inode(inode);
	if (err)
		return err;

	file_accessed(file);
	vma->vm_ops = &f2fs_file_vm_ops;
	return 0;
}
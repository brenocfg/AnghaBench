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
struct vm_area_struct {int vm_flags; int /*<<< orphan*/ * vm_ops; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_DAX (int /*<<< orphan*/ ) ; 
 int VM_HUGEPAGE ; 
 int VM_SYNC ; 
 int /*<<< orphan*/  ext4_dax_vm_ops ; 
 int /*<<< orphan*/  ext4_file_vm_ops ; 
 int /*<<< orphan*/  ext4_forced_shutdown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct inode *inode = file->f_mapping->host;

	if (unlikely(ext4_forced_shutdown(EXT4_SB(inode->i_sb))))
		return -EIO;

	/*
	 * We don't support synchronous mappings for non-DAX files. At least
	 * until someone comes with a sensible use case.
	 */
	if (!IS_DAX(file_inode(file)) && (vma->vm_flags & VM_SYNC))
		return -EOPNOTSUPP;

	file_accessed(file);
	if (IS_DAX(file_inode(file))) {
		vma->vm_ops = &ext4_dax_vm_ops;
		vma->vm_flags |= VM_HUGEPAGE;
	} else {
		vma->vm_ops = &ext4_file_vm_ops;
	}
	return 0;
}
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
struct vm_area_struct {int /*<<< orphan*/ * vm_ops; int /*<<< orphan*/  vm_flags; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct file {TYPE_1__* f_mapping; } ;
struct ext4_sb_info {struct dax_device* s_daxdev; } ;
struct dax_device {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 struct ext4_sb_info* EXT4_SB (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_DAX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_HUGEPAGE ; 
 int /*<<< orphan*/  daxdev_mapping_supported (struct vm_area_struct*,struct dax_device*) ; 
 int /*<<< orphan*/  ext4_dax_vm_ops ; 
 int /*<<< orphan*/  ext4_file_vm_ops ; 
 int /*<<< orphan*/  ext4_forced_shutdown (struct ext4_sb_info*) ; 
 int /*<<< orphan*/  file_accessed (struct file*) ; 
 int /*<<< orphan*/  file_inode (struct file*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_file_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct inode *inode = file->f_mapping->host;
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);
	struct dax_device *dax_dev = sbi->s_daxdev;

	if (unlikely(ext4_forced_shutdown(sbi)))
		return -EIO;

	/*
	 * We don't support synchronous mappings for non-DAX files and
	 * for DAX files if underneath dax_device is not synchronous.
	 */
	if (!daxdev_mapping_supported(vma, dax_dev))
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
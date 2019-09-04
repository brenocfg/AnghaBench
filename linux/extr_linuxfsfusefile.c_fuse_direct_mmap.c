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
struct vm_area_struct {int vm_flags; } ;
struct file {int /*<<< orphan*/  f_mapping; } ;

/* Variables and functions */
 int ENODEV ; 
 int VM_MAYSHARE ; 
 int generic_file_mmap (struct file*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fuse_direct_mmap(struct file *file, struct vm_area_struct *vma)
{
	/* Can't provide the coherency needed for MAP_SHARED */
	if (vma->vm_flags & VM_MAYSHARE)
		return -ENODEV;

	invalidate_inode_pages2(file->f_mapping);

	return generic_file_mmap(file, vma);
}
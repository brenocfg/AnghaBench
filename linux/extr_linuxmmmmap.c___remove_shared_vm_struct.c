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
struct vm_area_struct {int vm_flags; } ;
struct file {int dummy; } ;
struct address_space {int /*<<< orphan*/  i_mmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_writecount; } ;

/* Variables and functions */
 int VM_DENYWRITE ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* file_inode (struct file*) ; 
 int /*<<< orphan*/  flush_dcache_mmap_lock (struct address_space*) ; 
 int /*<<< orphan*/  flush_dcache_mmap_unlock (struct address_space*) ; 
 int /*<<< orphan*/  mapping_unmap_writable (struct address_space*) ; 
 int /*<<< orphan*/  vma_interval_tree_remove (struct vm_area_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __remove_shared_vm_struct(struct vm_area_struct *vma,
		struct file *file, struct address_space *mapping)
{
	if (vma->vm_flags & VM_DENYWRITE)
		atomic_inc(&file_inode(file)->i_writecount);
	if (vma->vm_flags & VM_SHARED)
		mapping_unmap_writable(mapping);

	flush_dcache_mmap_lock(mapping);
	vma_interval_tree_remove(vma, &mapping->i_mmap);
	flush_dcache_mmap_unlock(mapping);
}
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
struct writeback_control {int range_start; int range_end; scalar_t__ nr_to_write; int /*<<< orphan*/  sync_mode; } ;
struct vm_area_struct {int vm_pgoff; int vm_flags; int /*<<< orphan*/  vm_file; scalar_t__ vm_start; scalar_t__ vm_end; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 scalar_t__ LONG_MAX ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int PAGE_SIZE ; 
 int VM_SHARED ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 struct inode* file_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_cap_writeback_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  p9_debug (int /*<<< orphan*/ ,char*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  sync_inode (struct inode*,struct writeback_control*) ; 

__attribute__((used)) static void v9fs_mmap_vm_close(struct vm_area_struct *vma)
{
	struct inode *inode;

	struct writeback_control wbc = {
		.nr_to_write = LONG_MAX,
		.sync_mode = WB_SYNC_ALL,
		.range_start = vma->vm_pgoff * PAGE_SIZE,
		 /* absolute end, byte at end included */
		.range_end = vma->vm_pgoff * PAGE_SIZE +
			(vma->vm_end - vma->vm_start - 1),
	};

	if (!(vma->vm_flags & VM_SHARED))
		return;

	p9_debug(P9_DEBUG_VFS, "9p VMA close, %p, flushing", vma);

	inode = file_inode(vma->vm_file);

	if (!mapping_cap_writeback_dirty(inode->i_mapping))
		wbc.nr_to_write = 0;

	might_sleep();
	sync_inode(inode, &wbc);
}
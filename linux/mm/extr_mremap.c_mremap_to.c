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
struct vm_userfaultfd_ctx {int dummy; } ;
struct vm_area_struct {int vm_flags; unsigned long vm_start; scalar_t__ vm_pgoff; int /*<<< orphan*/  vm_file; } ;
struct mm_struct {int map_count; } ;
struct list_head {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long EINVAL ; 
 unsigned long ENOMEM ; 
 scalar_t__ IS_ERR (struct vm_area_struct*) ; 
 unsigned long MAP_FIXED ; 
 unsigned long MAP_SHARED ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PTR_ERR (struct vm_area_struct*) ; 
 unsigned long TASK_SIZE ; 
 int VM_MAYSHARE ; 
 TYPE_1__* current ; 
 unsigned long do_munmap (struct mm_struct*,unsigned long,unsigned long,struct list_head*) ; 
 unsigned long get_unmapped_area (int /*<<< orphan*/ ,unsigned long,unsigned long,scalar_t__,unsigned long) ; 
 unsigned long move_vma (struct vm_area_struct*,unsigned long,unsigned long,unsigned long,unsigned long,int*,struct vm_userfaultfd_ctx*,struct list_head*) ; 
 scalar_t__ offset_in_page (unsigned long) ; 
 int sysctl_max_map_count ; 
 int /*<<< orphan*/  vm_unacct_memory (unsigned long) ; 
 struct vm_area_struct* vma_to_resize (unsigned long,unsigned long,unsigned long,unsigned long*) ; 

__attribute__((used)) static unsigned long mremap_to(unsigned long addr, unsigned long old_len,
		unsigned long new_addr, unsigned long new_len, bool *locked,
		struct vm_userfaultfd_ctx *uf,
		struct list_head *uf_unmap_early,
		struct list_head *uf_unmap)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma;
	unsigned long ret = -EINVAL;
	unsigned long charged = 0;
	unsigned long map_flags;

	if (offset_in_page(new_addr))
		goto out;

	if (new_len > TASK_SIZE || new_addr > TASK_SIZE - new_len)
		goto out;

	/* Ensure the old/new locations do not overlap */
	if (addr + old_len > new_addr && new_addr + new_len > addr)
		goto out;

	/*
	 * move_vma() need us to stay 4 maps below the threshold, otherwise
	 * it will bail out at the very beginning.
	 * That is a problem if we have already unmaped the regions here
	 * (new_addr, and old_addr), because userspace will not know the
	 * state of the vma's after it gets -ENOMEM.
	 * So, to avoid such scenario we can pre-compute if the whole
	 * operation has high chances to success map-wise.
	 * Worst-scenario case is when both vma's (new_addr and old_addr) get
	 * split in 3 before unmaping it.
	 * That means 2 more maps (1 for each) to the ones we already hold.
	 * Check whether current map count plus 2 still leads us to 4 maps below
	 * the threshold, otherwise return -ENOMEM here to be more safe.
	 */
	if ((mm->map_count + 2) >= sysctl_max_map_count - 3)
		return -ENOMEM;

	ret = do_munmap(mm, new_addr, new_len, uf_unmap_early);
	if (ret)
		goto out;

	if (old_len >= new_len) {
		ret = do_munmap(mm, addr+new_len, old_len - new_len, uf_unmap);
		if (ret && old_len != new_len)
			goto out;
		old_len = new_len;
	}

	vma = vma_to_resize(addr, old_len, new_len, &charged);
	if (IS_ERR(vma)) {
		ret = PTR_ERR(vma);
		goto out;
	}

	map_flags = MAP_FIXED;
	if (vma->vm_flags & VM_MAYSHARE)
		map_flags |= MAP_SHARED;

	ret = get_unmapped_area(vma->vm_file, new_addr, new_len, vma->vm_pgoff +
				((addr - vma->vm_start) >> PAGE_SHIFT),
				map_flags);
	if (offset_in_page(ret))
		goto out1;

	ret = move_vma(vma, addr, old_len, new_len, new_addr, locked, uf,
		       uf_unmap);
	if (!(offset_in_page(ret)))
		goto out;
out1:
	vm_unacct_memory(charged);

out:
	return ret;
}
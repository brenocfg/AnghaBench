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
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; unsigned long vm_pgoff; unsigned long vm_flags; int /*<<< orphan*/  vm_page_prot; } ;
struct rb_node {int dummy; } ;
struct mm_struct {unsigned long def_flags; scalar_t__ map_count; unsigned long total_vm; unsigned long data_vm; unsigned long locked_vm; } ;
struct list_head {int dummy; } ;
typedef  unsigned long pgoff_t ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MAP_FIXED ; 
 int /*<<< orphan*/  NULL_VM_UFFD_CTX ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long VM_ACCOUNT ; 
 unsigned long VM_DATA_DEFAULT_FLAGS ; 
 unsigned long VM_EXEC ; 
 unsigned long VM_LOCKED ; 
 unsigned long VM_SOFTDIRTY ; 
 TYPE_1__* current ; 
 scalar_t__ do_munmap (struct mm_struct*,unsigned long,unsigned long,struct list_head*) ; 
 scalar_t__ find_vma_links (struct mm_struct*,unsigned long,unsigned long,struct vm_area_struct**,struct rb_node***,struct rb_node**) ; 
 int get_unmapped_area (int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  may_expand_vm (struct mm_struct*,unsigned long,unsigned long) ; 
 int mlock_future_check (struct mm_struct*,unsigned long,unsigned long) ; 
 scalar_t__ offset_in_page (int) ; 
 int /*<<< orphan*/  perf_event_mmap (struct vm_area_struct*) ; 
 scalar_t__ security_vm_enough_memory_mm (struct mm_struct*,unsigned long) ; 
 scalar_t__ sysctl_max_map_count ; 
 struct vm_area_struct* vm_area_alloc (struct mm_struct*) ; 
 int /*<<< orphan*/  vm_get_page_prot (unsigned long) ; 
 int /*<<< orphan*/  vm_unacct_memory (unsigned long) ; 
 int /*<<< orphan*/  vma_link (struct mm_struct*,struct vm_area_struct*,struct vm_area_struct*,struct rb_node**,struct rb_node*) ; 
 struct vm_area_struct* vma_merge (struct mm_struct*,struct vm_area_struct*,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_set_anonymous (struct vm_area_struct*) ; 

__attribute__((used)) static int do_brk_flags(unsigned long addr, unsigned long len, unsigned long flags, struct list_head *uf)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma, *prev;
	struct rb_node **rb_link, *rb_parent;
	pgoff_t pgoff = addr >> PAGE_SHIFT;
	int error;

	/* Until we need other flags, refuse anything except VM_EXEC. */
	if ((flags & (~VM_EXEC)) != 0)
		return -EINVAL;
	flags |= VM_DATA_DEFAULT_FLAGS | VM_ACCOUNT | mm->def_flags;

	error = get_unmapped_area(NULL, addr, len, 0, MAP_FIXED);
	if (offset_in_page(error))
		return error;

	error = mlock_future_check(mm, mm->def_flags, len);
	if (error)
		return error;

	/*
	 * Clear old maps.  this also does some error checking for us
	 */
	while (find_vma_links(mm, addr, addr + len, &prev, &rb_link,
			      &rb_parent)) {
		if (do_munmap(mm, addr, len, uf))
			return -ENOMEM;
	}

	/* Check against address space limits *after* clearing old maps... */
	if (!may_expand_vm(mm, flags, len >> PAGE_SHIFT))
		return -ENOMEM;

	if (mm->map_count > sysctl_max_map_count)
		return -ENOMEM;

	if (security_vm_enough_memory_mm(mm, len >> PAGE_SHIFT))
		return -ENOMEM;

	/* Can we just expand an old private anonymous mapping? */
	vma = vma_merge(mm, prev, addr, addr + len, flags,
			NULL, NULL, pgoff, NULL, NULL_VM_UFFD_CTX);
	if (vma)
		goto out;

	/*
	 * create a vma struct for an anonymous mapping
	 */
	vma = vm_area_alloc(mm);
	if (!vma) {
		vm_unacct_memory(len >> PAGE_SHIFT);
		return -ENOMEM;
	}

	vma_set_anonymous(vma);
	vma->vm_start = addr;
	vma->vm_end = addr + len;
	vma->vm_pgoff = pgoff;
	vma->vm_flags = flags;
	vma->vm_page_prot = vm_get_page_prot(flags);
	vma_link(mm, vma, prev, rb_link, rb_parent);
out:
	perf_event_mmap(vma);
	mm->total_vm += len >> PAGE_SHIFT;
	mm->data_vm += len >> PAGE_SHIFT;
	if (flags & VM_LOCKED)
		mm->locked_vm += (len >> PAGE_SHIFT);
	vma->vm_flags |= VM_SOFTDIRTY;
	return 0;
}
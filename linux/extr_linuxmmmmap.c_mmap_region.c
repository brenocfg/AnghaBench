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
typedef  int vm_flags_t ;
struct vm_area_struct {unsigned long vm_start; unsigned long vm_end; int vm_flags; unsigned long vm_pgoff; struct file* vm_file; int /*<<< orphan*/  vm_page_prot; } ;
struct rb_node {int dummy; } ;
struct mm_struct {unsigned long locked_vm; } ;
struct list_head {int dummy; } ;
struct file {int /*<<< orphan*/  f_mapping; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 unsigned long ENOMEM ; 
 int /*<<< orphan*/  NULL_VM_UFFD_CTX ; 
 unsigned long PAGE_SHIFT ; 
 int VM_ACCOUNT ; 
 int VM_DENYWRITE ; 
 int VM_LOCKED ; 
 int VM_LOCKED_CLEAR_MASK ; 
 int VM_SHARED ; 
 int VM_SOFTDIRTY ; 
 int VM_SPECIAL ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ accountable_mapping (struct file*,int) ; 
 int /*<<< orphan*/  allow_write_access (struct file*) ; 
 int call_mmap (struct file*,struct vm_area_struct*) ; 
 unsigned long count_vma_pages_range (struct mm_struct*,unsigned long,unsigned long) ; 
 TYPE_1__* current ; 
 int deny_write_access (struct file*) ; 
 scalar_t__ do_munmap (struct mm_struct*,unsigned long,unsigned long,struct list_head*) ; 
 scalar_t__ find_vma_links (struct mm_struct*,unsigned long,unsigned long,struct vm_area_struct**,struct rb_node***,struct rb_node**) ; 
 int /*<<< orphan*/  fput (struct file*) ; 
 struct file* get_file (struct file*) ; 
 struct vm_area_struct* get_gate_vma (struct mm_struct*) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int mapping_map_writable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_unmap_writable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  may_expand_vm (struct mm_struct*,int,unsigned long) ; 
 int /*<<< orphan*/  perf_event_mmap (struct vm_area_struct*) ; 
 scalar_t__ security_vm_enough_memory_mm (struct mm_struct*,unsigned long) ; 
 int shmem_zero_setup (struct vm_area_struct*) ; 
 int /*<<< orphan*/  unmap_region (struct mm_struct*,struct vm_area_struct*,struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  uprobe_mmap (struct vm_area_struct*) ; 
 struct vm_area_struct* vm_area_alloc (struct mm_struct*) ; 
 int /*<<< orphan*/  vm_area_free (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vm_get_page_prot (int) ; 
 int /*<<< orphan*/  vm_stat_account (struct mm_struct*,int,unsigned long) ; 
 int /*<<< orphan*/  vm_unacct_memory (unsigned long) ; 
 scalar_t__ vma_is_dax (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_link (struct mm_struct*,struct vm_area_struct*,struct vm_area_struct*,struct rb_node**,struct rb_node*) ; 
 struct vm_area_struct* vma_merge (struct mm_struct*,struct vm_area_struct*,unsigned long,unsigned long,int,int /*<<< orphan*/ *,struct file*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vma_set_anonymous (struct vm_area_struct*) ; 
 int /*<<< orphan*/  vma_set_page_prot (struct vm_area_struct*) ; 

unsigned long mmap_region(struct file *file, unsigned long addr,
		unsigned long len, vm_flags_t vm_flags, unsigned long pgoff,
		struct list_head *uf)
{
	struct mm_struct *mm = current->mm;
	struct vm_area_struct *vma, *prev;
	int error;
	struct rb_node **rb_link, *rb_parent;
	unsigned long charged = 0;

	/* Check against address space limit. */
	if (!may_expand_vm(mm, vm_flags, len >> PAGE_SHIFT)) {
		unsigned long nr_pages;

		/*
		 * MAP_FIXED may remove pages of mappings that intersects with
		 * requested mapping. Account for the pages it would unmap.
		 */
		nr_pages = count_vma_pages_range(mm, addr, addr + len);

		if (!may_expand_vm(mm, vm_flags,
					(len >> PAGE_SHIFT) - nr_pages))
			return -ENOMEM;
	}

	/* Clear old maps */
	while (find_vma_links(mm, addr, addr + len, &prev, &rb_link,
			      &rb_parent)) {
		if (do_munmap(mm, addr, len, uf))
			return -ENOMEM;
	}

	/*
	 * Private writable mapping: check memory availability
	 */
	if (accountable_mapping(file, vm_flags)) {
		charged = len >> PAGE_SHIFT;
		if (security_vm_enough_memory_mm(mm, charged))
			return -ENOMEM;
		vm_flags |= VM_ACCOUNT;
	}

	/*
	 * Can we just expand an old mapping?
	 */
	vma = vma_merge(mm, prev, addr, addr + len, vm_flags,
			NULL, file, pgoff, NULL, NULL_VM_UFFD_CTX);
	if (vma)
		goto out;

	/*
	 * Determine the object being mapped and call the appropriate
	 * specific mapper. the address has already been validated, but
	 * not unmapped, but the maps are removed from the list.
	 */
	vma = vm_area_alloc(mm);
	if (!vma) {
		error = -ENOMEM;
		goto unacct_error;
	}

	vma->vm_start = addr;
	vma->vm_end = addr + len;
	vma->vm_flags = vm_flags;
	vma->vm_page_prot = vm_get_page_prot(vm_flags);
	vma->vm_pgoff = pgoff;

	if (file) {
		if (vm_flags & VM_DENYWRITE) {
			error = deny_write_access(file);
			if (error)
				goto free_vma;
		}
		if (vm_flags & VM_SHARED) {
			error = mapping_map_writable(file->f_mapping);
			if (error)
				goto allow_write_and_free_vma;
		}

		/* ->mmap() can change vma->vm_file, but must guarantee that
		 * vma_link() below can deny write-access if VM_DENYWRITE is set
		 * and map writably if VM_SHARED is set. This usually means the
		 * new file must not have been exposed to user-space, yet.
		 */
		vma->vm_file = get_file(file);
		error = call_mmap(file, vma);
		if (error)
			goto unmap_and_free_vma;

		/* Can addr have changed??
		 *
		 * Answer: Yes, several device drivers can do it in their
		 *         f_op->mmap method. -DaveM
		 * Bug: If addr is changed, prev, rb_link, rb_parent should
		 *      be updated for vma_link()
		 */
		WARN_ON_ONCE(addr != vma->vm_start);

		addr = vma->vm_start;
		vm_flags = vma->vm_flags;
	} else if (vm_flags & VM_SHARED) {
		error = shmem_zero_setup(vma);
		if (error)
			goto free_vma;
	} else {
		vma_set_anonymous(vma);
	}

	vma_link(mm, vma, prev, rb_link, rb_parent);
	/* Once vma denies write, undo our temporary denial count */
	if (file) {
		if (vm_flags & VM_SHARED)
			mapping_unmap_writable(file->f_mapping);
		if (vm_flags & VM_DENYWRITE)
			allow_write_access(file);
	}
	file = vma->vm_file;
out:
	perf_event_mmap(vma);

	vm_stat_account(mm, vm_flags, len >> PAGE_SHIFT);
	if (vm_flags & VM_LOCKED) {
		if ((vm_flags & VM_SPECIAL) || vma_is_dax(vma) ||
					is_vm_hugetlb_page(vma) ||
					vma == get_gate_vma(current->mm))
			vma->vm_flags &= VM_LOCKED_CLEAR_MASK;
		else
			mm->locked_vm += (len >> PAGE_SHIFT);
	}

	if (file)
		uprobe_mmap(vma);

	/*
	 * New (or expanded) vma always get soft dirty status.
	 * Otherwise user-space soft-dirty page tracker won't
	 * be able to distinguish situation when vma area unmapped,
	 * then new mapped in-place (which must be aimed as
	 * a completely new data area).
	 */
	vma->vm_flags |= VM_SOFTDIRTY;

	vma_set_page_prot(vma);

	return addr;

unmap_and_free_vma:
	vma->vm_file = NULL;
	fput(file);

	/* Undo any partial mapping done by a device driver. */
	unmap_region(mm, vma, prev, vma->vm_start, vma->vm_end);
	charged = 0;
	if (vm_flags & VM_SHARED)
		mapping_unmap_writable(file->f_mapping);
allow_write_and_free_vma:
	if (vm_flags & VM_DENYWRITE)
		allow_write_access(file);
free_vma:
	vm_area_free(vma);
unacct_error:
	if (charged)
		vm_unacct_memory(charged);
	return error;
}
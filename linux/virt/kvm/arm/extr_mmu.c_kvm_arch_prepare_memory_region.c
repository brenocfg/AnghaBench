#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {scalar_t__ vm_start; int vm_flags; scalar_t__ vm_pgoff; int /*<<< orphan*/  vm_end; } ;
struct kvm_userspace_memory_region {scalar_t__ userspace_addr; scalar_t__ memory_size; int flags; scalar_t__ guest_phys_addr; } ;
struct kvm_memory_slot {int base_gfn; int npages; int flags; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; } ;
typedef  int phys_addr_t ;
typedef  scalar_t__ hva_t ;
typedef  scalar_t__ gpa_t ;
typedef  enum kvm_mr_change { ____Placeholder_kvm_mr_change } kvm_mr_change ;
struct TYPE_4__ {TYPE_1__* mm; } ;
struct TYPE_3__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int EPERM ; 
 int KVM_MEM_LOG_DIRTY_PAGES ; 
 int KVM_MEM_READONLY ; 
 int KVM_MR_CREATE ; 
 int KVM_MR_FLAGS_ONLY ; 
 int KVM_MR_MOVE ; 
 int PAGE_SHIFT ; 
 int VM_PFNMAP ; 
 int VM_WRITE ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma (TYPE_1__*,scalar_t__) ; 
 int kvm_phys_addr_ioremap (struct kvm*,scalar_t__,int,scalar_t__,int) ; 
 int kvm_phys_size (struct kvm*) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stage2_flush_memslot (struct kvm*,struct kvm_memory_slot*) ; 
 int /*<<< orphan*/  unmap_stage2_range (struct kvm*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int kvm_arch_prepare_memory_region(struct kvm *kvm,
				   struct kvm_memory_slot *memslot,
				   const struct kvm_userspace_memory_region *mem,
				   enum kvm_mr_change change)
{
	hva_t hva = mem->userspace_addr;
	hva_t reg_end = hva + mem->memory_size;
	bool writable = !(mem->flags & KVM_MEM_READONLY);
	int ret = 0;

	if (change != KVM_MR_CREATE && change != KVM_MR_MOVE &&
			change != KVM_MR_FLAGS_ONLY)
		return 0;

	/*
	 * Prevent userspace from creating a memory region outside of the IPA
	 * space addressable by the KVM guest IPA space.
	 */
	if (memslot->base_gfn + memslot->npages >=
	    (kvm_phys_size(kvm) >> PAGE_SHIFT))
		return -EFAULT;

	down_read(&current->mm->mmap_sem);
	/*
	 * A memory region could potentially cover multiple VMAs, and any holes
	 * between them, so iterate over all of them to find out if we can map
	 * any of them right now.
	 *
	 *     +--------------------------------------------+
	 * +---------------+----------------+   +----------------+
	 * |   : VMA 1     |      VMA 2     |   |    VMA 3  :    |
	 * +---------------+----------------+   +----------------+
	 *     |               memory region                |
	 *     +--------------------------------------------+
	 */
	do {
		struct vm_area_struct *vma = find_vma(current->mm, hva);
		hva_t vm_start, vm_end;

		if (!vma || vma->vm_start >= reg_end)
			break;

		/*
		 * Mapping a read-only VMA is only allowed if the
		 * memory region is configured as read-only.
		 */
		if (writable && !(vma->vm_flags & VM_WRITE)) {
			ret = -EPERM;
			break;
		}

		/*
		 * Take the intersection of this VMA with the memory region
		 */
		vm_start = max(hva, vma->vm_start);
		vm_end = min(reg_end, vma->vm_end);

		if (vma->vm_flags & VM_PFNMAP) {
			gpa_t gpa = mem->guest_phys_addr +
				    (vm_start - mem->userspace_addr);
			phys_addr_t pa;

			pa = (phys_addr_t)vma->vm_pgoff << PAGE_SHIFT;
			pa += vm_start - vma->vm_start;

			/* IO region dirty page logging not allowed */
			if (memslot->flags & KVM_MEM_LOG_DIRTY_PAGES) {
				ret = -EINVAL;
				goto out;
			}

			ret = kvm_phys_addr_ioremap(kvm, gpa, pa,
						    vm_end - vm_start,
						    writable);
			if (ret)
				break;
		}
		hva = vm_end;
	} while (hva < reg_end);

	if (change == KVM_MR_FLAGS_ONLY)
		goto out;

	spin_lock(&kvm->mmu_lock);
	if (ret)
		unmap_stage2_range(kvm, mem->guest_phys_addr, mem->memory_size);
	else
		stage2_flush_memslot(kvm, memslot);
	spin_unlock(&kvm->mmu_lock);
out:
	up_read(&current->mm->mmap_sem);
	return ret;
}
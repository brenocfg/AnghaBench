#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct kvm_mmu_memory_cache {int dummy; } ;
struct TYPE_4__ {struct kvm_mmu_memory_cache mmu_page_cache; } ;
struct kvm_vcpu {struct kvm* kvm; TYPE_1__ arch; } ;
struct kvm_memory_slot {int userspace_addr; int base_gfn; } ;
struct kvm {unsigned long mmu_notifier_seq; int /*<<< orphan*/  mmu_lock; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  scalar_t__ kvm_pfn_t ;
typedef  int gfn_t ;
struct TYPE_6__ {TYPE_2__* mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  mmap_sem; } ;

/* Variables and functions */
 int EFAULT ; 
 unsigned long FSC_PERM ; 
 int /*<<< orphan*/  KVM_MMU_CACHE_MIN_PAGES ; 
 int /*<<< orphan*/  KVM_NR_MEM_OBJS ; 
 scalar_t__ KVM_PFN_ERR_HWPOISON ; 
 unsigned long KVM_S2PTE_FLAG_IS_IOMAP ; 
 unsigned long KVM_S2_FLAG_LOGGING_ACTIVE ; 
 int /*<<< orphan*/  PAGE_S2 ; 
 int /*<<< orphan*/  PAGE_S2_DEVICE ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int PMD_MASK ; 
 scalar_t__ PMD_SIZE ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  clean_dcache_guest_page (scalar_t__,scalar_t__) ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 struct vm_area_struct* find_vma_intersection (TYPE_2__*,unsigned long,unsigned long) ; 
 scalar_t__ gfn_to_pfn_prot (struct kvm*,int,int,int*) ; 
 int /*<<< orphan*/  invalidate_icache_guest_page (scalar_t__,scalar_t__) ; 
 scalar_t__ is_error_noslot_pfn (scalar_t__) ; 
 int /*<<< orphan*/  kvm_err (char*,...) ; 
 scalar_t__ kvm_is_device_pfn (scalar_t__) ; 
 int kvm_is_write_fault (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (scalar_t__) ; 
 int /*<<< orphan*/  kvm_s2pmd_mkexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s2pmd_mkwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s2pte_mkexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s2pte_mkwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_send_hwpoison_signal (unsigned long,struct vm_area_struct*) ; 
 int /*<<< orphan*/  kvm_set_pfn_accessed (scalar_t__) ; 
 int /*<<< orphan*/  kvm_set_pfn_dirty (scalar_t__) ; 
 int kvm_vcpu_trap_is_iabt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mark_page_dirty (struct kvm*,int) ; 
 int memslot_is_logging (struct kvm_memory_slot*) ; 
 scalar_t__ mmu_notifier_retry (struct kvm*,unsigned long) ; 
 int mmu_topup_memory_cache (struct kvm_mmu_memory_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_pmd (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfn_pte (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkhuge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ stage2_is_exec (struct kvm*,int) ; 
 int stage2_set_pmd_huge (struct kvm*,struct kvm_mmu_memory_cache*,int,int /*<<< orphan*/ *) ; 
 int stage2_set_pte (struct kvm*,struct kvm_mmu_memory_cache*,int,int /*<<< orphan*/ *,unsigned long) ; 
 int transparent_hugepage_adjust (scalar_t__*,int*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 scalar_t__ vma_kernel_pagesize (struct vm_area_struct*) ; 

__attribute__((used)) static int user_mem_abort(struct kvm_vcpu *vcpu, phys_addr_t fault_ipa,
			  struct kvm_memory_slot *memslot, unsigned long hva,
			  unsigned long fault_status)
{
	int ret;
	bool write_fault, exec_fault, writable, hugetlb = false, force_pte = false;
	unsigned long mmu_seq;
	gfn_t gfn = fault_ipa >> PAGE_SHIFT;
	struct kvm *kvm = vcpu->kvm;
	struct kvm_mmu_memory_cache *memcache = &vcpu->arch.mmu_page_cache;
	struct vm_area_struct *vma;
	kvm_pfn_t pfn;
	pgprot_t mem_type = PAGE_S2;
	bool logging_active = memslot_is_logging(memslot);
	unsigned long flags = 0;

	write_fault = kvm_is_write_fault(vcpu);
	exec_fault = kvm_vcpu_trap_is_iabt(vcpu);
	VM_BUG_ON(write_fault && exec_fault);

	if (fault_status == FSC_PERM && !write_fault && !exec_fault) {
		kvm_err("Unexpected L2 read permission error\n");
		return -EFAULT;
	}

	/* Let's check if we will get back a huge page backed by hugetlbfs */
	down_read(&current->mm->mmap_sem);
	vma = find_vma_intersection(current->mm, hva, hva + 1);
	if (unlikely(!vma)) {
		kvm_err("Failed to find VMA for hva 0x%lx\n", hva);
		up_read(&current->mm->mmap_sem);
		return -EFAULT;
	}

	if (vma_kernel_pagesize(vma) == PMD_SIZE && !logging_active) {
		hugetlb = true;
		gfn = (fault_ipa & PMD_MASK) >> PAGE_SHIFT;
	} else {
		/*
		 * Pages belonging to memslots that don't have the same
		 * alignment for userspace and IPA cannot be mapped using
		 * block descriptors even if the pages belong to a THP for
		 * the process, because the stage-2 block descriptor will
		 * cover more than a single THP and we loose atomicity for
		 * unmapping, updates, and splits of the THP or other pages
		 * in the stage-2 block range.
		 */
		if ((memslot->userspace_addr & ~PMD_MASK) !=
		    ((memslot->base_gfn << PAGE_SHIFT) & ~PMD_MASK))
			force_pte = true;
	}
	up_read(&current->mm->mmap_sem);

	/* We need minimum second+third level pages */
	ret = mmu_topup_memory_cache(memcache, KVM_MMU_CACHE_MIN_PAGES,
				     KVM_NR_MEM_OBJS);
	if (ret)
		return ret;

	mmu_seq = vcpu->kvm->mmu_notifier_seq;
	/*
	 * Ensure the read of mmu_notifier_seq happens before we call
	 * gfn_to_pfn_prot (which calls get_user_pages), so that we don't risk
	 * the page we just got a reference to gets unmapped before we have a
	 * chance to grab the mmu_lock, which ensure that if the page gets
	 * unmapped afterwards, the call to kvm_unmap_hva will take it away
	 * from us again properly. This smp_rmb() interacts with the smp_wmb()
	 * in kvm_mmu_notifier_invalidate_<page|range_end>.
	 */
	smp_rmb();

	pfn = gfn_to_pfn_prot(kvm, gfn, write_fault, &writable);
	if (pfn == KVM_PFN_ERR_HWPOISON) {
		kvm_send_hwpoison_signal(hva, vma);
		return 0;
	}
	if (is_error_noslot_pfn(pfn))
		return -EFAULT;

	if (kvm_is_device_pfn(pfn)) {
		mem_type = PAGE_S2_DEVICE;
		flags |= KVM_S2PTE_FLAG_IS_IOMAP;
	} else if (logging_active) {
		/*
		 * Faults on pages in a memslot with logging enabled
		 * should not be mapped with huge pages (it introduces churn
		 * and performance degradation), so force a pte mapping.
		 */
		force_pte = true;
		flags |= KVM_S2_FLAG_LOGGING_ACTIVE;

		/*
		 * Only actually map the page as writable if this was a write
		 * fault.
		 */
		if (!write_fault)
			writable = false;
	}

	spin_lock(&kvm->mmu_lock);
	if (mmu_notifier_retry(kvm, mmu_seq))
		goto out_unlock;

	if (!hugetlb && !force_pte)
		hugetlb = transparent_hugepage_adjust(&pfn, &fault_ipa);

	if (hugetlb) {
		pmd_t new_pmd = pfn_pmd(pfn, mem_type);
		new_pmd = pmd_mkhuge(new_pmd);
		if (writable) {
			new_pmd = kvm_s2pmd_mkwrite(new_pmd);
			kvm_set_pfn_dirty(pfn);
		}

		if (fault_status != FSC_PERM)
			clean_dcache_guest_page(pfn, PMD_SIZE);

		if (exec_fault) {
			new_pmd = kvm_s2pmd_mkexec(new_pmd);
			invalidate_icache_guest_page(pfn, PMD_SIZE);
		} else if (fault_status == FSC_PERM) {
			/* Preserve execute if XN was already cleared */
			if (stage2_is_exec(kvm, fault_ipa))
				new_pmd = kvm_s2pmd_mkexec(new_pmd);
		}

		ret = stage2_set_pmd_huge(kvm, memcache, fault_ipa, &new_pmd);
	} else {
		pte_t new_pte = pfn_pte(pfn, mem_type);

		if (writable) {
			new_pte = kvm_s2pte_mkwrite(new_pte);
			kvm_set_pfn_dirty(pfn);
			mark_page_dirty(kvm, gfn);
		}

		if (fault_status != FSC_PERM)
			clean_dcache_guest_page(pfn, PAGE_SIZE);

		if (exec_fault) {
			new_pte = kvm_s2pte_mkexec(new_pte);
			invalidate_icache_guest_page(pfn, PAGE_SIZE);
		} else if (fault_status == FSC_PERM) {
			/* Preserve execute if XN was already cleared */
			if (stage2_is_exec(kvm, fault_ipa))
				new_pte = kvm_s2pte_mkexec(new_pte);
		}

		ret = stage2_set_pte(kvm, memcache, fault_ipa, &new_pte, flags);
	}

out_unlock:
	spin_unlock(&kvm->mmu_lock);
	kvm_set_pfn_accessed(pfn);
	kvm_release_pfn_clean(pfn);
	return ret;
}
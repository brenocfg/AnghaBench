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
struct kvm_mmu_memory_cache {int /*<<< orphan*/  member_0; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_NR_MEM_OBJS ; 
 int /*<<< orphan*/  KVM_S2PTE_FLAG_IS_IOMAP ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_S2_DEVICE ; 
 unsigned long PAGE_SIZE ; 
 unsigned long __phys_to_pfn (unsigned long) ; 
 int /*<<< orphan*/  kvm_mmu_cache_min_pages (struct kvm*) ; 
 int /*<<< orphan*/  kvm_pfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s2pte_mkwrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_free_memory_cache (struct kvm_mmu_memory_cache*) ; 
 int mmu_topup_memory_cache (struct kvm_mmu_memory_cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int stage2_set_pte (struct kvm*,struct kvm_mmu_memory_cache*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int kvm_phys_addr_ioremap(struct kvm *kvm, phys_addr_t guest_ipa,
			  phys_addr_t pa, unsigned long size, bool writable)
{
	phys_addr_t addr, end;
	int ret = 0;
	unsigned long pfn;
	struct kvm_mmu_memory_cache cache = { 0, };

	end = (guest_ipa + size + PAGE_SIZE - 1) & PAGE_MASK;
	pfn = __phys_to_pfn(pa);

	for (addr = guest_ipa; addr < end; addr += PAGE_SIZE) {
		pte_t pte = kvm_pfn_pte(pfn, PAGE_S2_DEVICE);

		if (writable)
			pte = kvm_s2pte_mkwrite(pte);

		ret = mmu_topup_memory_cache(&cache,
					     kvm_mmu_cache_min_pages(kvm),
					     KVM_NR_MEM_OBJS);
		if (ret)
			goto out;
		spin_lock(&kvm->mmu_lock);
		ret = stage2_set_pte(kvm, &cache, addr, &pte,
						KVM_S2PTE_FLAG_IS_IOMAP);
		spin_unlock(&kvm->mmu_lock);
		if (ret)
			goto out;

		pfn++;
	}

out:
	mmu_free_memory_cache(&cache);
	return ret;
}
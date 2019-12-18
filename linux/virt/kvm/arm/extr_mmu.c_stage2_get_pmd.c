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
struct kvm_mmu_memory_cache {int dummy; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmu_memory_cache_alloc (struct kvm_mmu_memory_cache*) ; 
 int /*<<< orphan*/ * stage2_get_pud (struct kvm*,struct kvm_mmu_memory_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stage2_pmd_offset (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stage2_pud_huge (struct kvm*,int /*<<< orphan*/ ) ; 
 scalar_t__ stage2_pud_none (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage2_pud_populate (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pmd_t *stage2_get_pmd(struct kvm *kvm, struct kvm_mmu_memory_cache *cache,
			     phys_addr_t addr)
{
	pud_t *pud;
	pmd_t *pmd;

	pud = stage2_get_pud(kvm, cache, addr);
	if (!pud || stage2_pud_huge(kvm, *pud))
		return NULL;

	if (stage2_pud_none(kvm, *pud)) {
		if (!cache)
			return NULL;
		pmd = mmu_memory_cache_alloc(cache);
		stage2_pud_populate(kvm, pud, pmd);
		get_page(virt_to_page(pud));
	}

	return stage2_pmd_offset(kvm, pud, addr);
}
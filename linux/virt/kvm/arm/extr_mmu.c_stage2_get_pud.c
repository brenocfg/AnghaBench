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
struct kvm_mmu_memory_cache {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pgd; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmu_memory_cache_alloc (struct kvm_mmu_memory_cache*) ; 
 int stage2_pgd_index (struct kvm*,int /*<<< orphan*/ ) ; 
 scalar_t__ stage2_pgd_none (struct kvm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stage2_pgd_populate (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stage2_pud_offset (struct kvm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static pud_t *stage2_get_pud(struct kvm *kvm, struct kvm_mmu_memory_cache *cache,
			     phys_addr_t addr)
{
	pgd_t *pgd;
	pud_t *pud;

	pgd = kvm->arch.pgd + stage2_pgd_index(kvm, addr);
	if (stage2_pgd_none(kvm, *pgd)) {
		if (!cache)
			return NULL;
		pud = mmu_memory_cache_alloc(cache);
		stage2_pgd_populate(kvm, pgd, pud);
		get_page(virt_to_page(pgd));
	}

	return stage2_pud_offset(kvm, pgd, addr);
}
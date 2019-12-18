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
struct kvm_memory_slot {scalar_t__ base_gfn; int npages; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pgd; } ;
struct kvm {TYPE_1__ arch; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 scalar_t__ PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  stage2_flush_puds (struct kvm*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ stage2_pgd_addr_end (struct kvm*,scalar_t__,scalar_t__) ; 
 int stage2_pgd_index (struct kvm*,scalar_t__) ; 
 int /*<<< orphan*/  stage2_pgd_none (struct kvm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stage2_flush_memslot(struct kvm *kvm,
				 struct kvm_memory_slot *memslot)
{
	phys_addr_t addr = memslot->base_gfn << PAGE_SHIFT;
	phys_addr_t end = addr + PAGE_SIZE * memslot->npages;
	phys_addr_t next;
	pgd_t *pgd;

	pgd = kvm->arch.pgd + stage2_pgd_index(kvm, addr);
	do {
		next = stage2_pgd_addr_end(kvm, addr, end);
		if (!stage2_pgd_none(kvm, *pgd))
			stage2_flush_puds(kvm, pgd, addr, next);
	} while (pgd++, addr = next, addr != end);
}
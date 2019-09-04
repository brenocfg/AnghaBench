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
struct mmu_gather {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 unsigned long PGDIR_MASK ; 
 int /*<<< orphan*/  free_pud_range (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 unsigned long p4d_addr_end (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  p4d_free_tlb (struct mmu_gather*,int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ p4d_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pgd_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void free_p4d_range(struct mmu_gather *tlb, pgd_t *pgd,
				unsigned long addr, unsigned long end,
				unsigned long floor, unsigned long ceiling)
{
	p4d_t *p4d;
	unsigned long next;
	unsigned long start;

	start = addr;
	p4d = p4d_offset(pgd, addr);
	do {
		next = p4d_addr_end(addr, end);
		if (p4d_none_or_clear_bad(p4d))
			continue;
		free_pud_range(tlb, p4d, addr, next, floor, ceiling);
	} while (p4d++, addr = next, addr != end);

	start &= PGDIR_MASK;
	if (start < floor)
		return;
	if (ceiling) {
		ceiling &= PGDIR_MASK;
		if (!ceiling)
			return;
	}
	if (end - 1 > ceiling - 1)
		return;

	p4d = p4d_offset(pgd, start);
	pgd_clear(pgd);
	p4d_free_tlb(tlb, p4d, start);
}
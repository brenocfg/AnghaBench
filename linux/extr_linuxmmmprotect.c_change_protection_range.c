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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ change_p4d_range (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dec_tlb_flush_pending (struct mm_struct*) ; 
 int /*<<< orphan*/  flush_cache_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_range (struct vm_area_struct*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  inc_tlb_flush_pending (struct mm_struct*) ; 
 unsigned long pgd_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ pgd_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 

__attribute__((used)) static unsigned long change_protection_range(struct vm_area_struct *vma,
		unsigned long addr, unsigned long end, pgprot_t newprot,
		int dirty_accountable, int prot_numa)
{
	struct mm_struct *mm = vma->vm_mm;
	pgd_t *pgd;
	unsigned long next;
	unsigned long start = addr;
	unsigned long pages = 0;

	BUG_ON(addr >= end);
	pgd = pgd_offset(mm, addr);
	flush_cache_range(vma, addr, end);
	inc_tlb_flush_pending(mm);
	do {
		next = pgd_addr_end(addr, end);
		if (pgd_none_or_clear_bad(pgd))
			continue;
		pages += change_p4d_range(vma, pgd, addr, next, newprot,
				 dirty_accountable, prot_numa);
	} while (pgd++, addr = next, addr != end);

	/* Only flush the TLB if we actually modified any entries: */
	if (pages)
		flush_tlb_range(vma, start, end);
	dec_tlb_flush_pending(mm);

	return pages;
}
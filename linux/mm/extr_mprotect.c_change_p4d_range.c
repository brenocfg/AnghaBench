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
struct vm_area_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 scalar_t__ change_pud_range (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,int,int) ; 
 unsigned long p4d_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ p4d_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline unsigned long change_p4d_range(struct vm_area_struct *vma,
		pgd_t *pgd, unsigned long addr, unsigned long end,
		pgprot_t newprot, int dirty_accountable, int prot_numa)
{
	p4d_t *p4d;
	unsigned long next;
	unsigned long pages = 0;

	p4d = p4d_offset(pgd, addr);
	do {
		next = p4d_addr_end(addr, end);
		if (p4d_none_or_clear_bad(p4d))
			continue;
		pages += change_pud_range(vma, p4d, addr, next, newprot,
				 dirty_accountable, prot_numa);
	} while (p4d++, addr = next, addr != end);

	return pages;
}
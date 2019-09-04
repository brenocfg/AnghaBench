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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct vm_area_struct {int dummy; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 unsigned long p4d_addr_end (unsigned long,unsigned long) ; 
 scalar_t__ p4d_none_or_clear_bad (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int unuse_pud_range (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,unsigned long,int /*<<< orphan*/ ,struct page*) ; 

__attribute__((used)) static inline int unuse_p4d_range(struct vm_area_struct *vma, pgd_t *pgd,
				unsigned long addr, unsigned long end,
				swp_entry_t entry, struct page *page)
{
	p4d_t *p4d;
	unsigned long next;
	int ret;

	p4d = p4d_offset(pgd, addr);
	do {
		next = p4d_addr_end(addr, end);
		if (p4d_none_or_clear_bad(p4d))
			continue;
		ret = unuse_pud_range(vma, p4d, addr, next, entry, page);
		if (ret)
			return ret;
	} while (p4d++, addr = next, addr != end);
	return 0;
}
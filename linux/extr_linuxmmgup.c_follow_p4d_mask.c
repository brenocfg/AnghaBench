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
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  P4D_SHIFT ; 
 int /*<<< orphan*/  __hugepd (int /*<<< orphan*/ ) ; 
 struct page* follow_huge_pd (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 struct page* follow_pud_mask (struct vm_area_struct*,unsigned long,int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 
 scalar_t__ is_hugepd (int /*<<< orphan*/ ) ; 
 struct page* no_page_table (struct vm_area_struct*,unsigned int) ; 
 int /*<<< orphan*/  p4d_bad (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p4d_huge (int /*<<< orphan*/ ) ; 
 scalar_t__ p4d_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  p4d_val (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct page *follow_p4d_mask(struct vm_area_struct *vma,
				    unsigned long address, pgd_t *pgdp,
				    unsigned int flags, unsigned int *page_mask)
{
	p4d_t *p4d;
	struct page *page;

	p4d = p4d_offset(pgdp, address);
	if (p4d_none(*p4d))
		return no_page_table(vma, flags);
	BUILD_BUG_ON(p4d_huge(*p4d));
	if (unlikely(p4d_bad(*p4d)))
		return no_page_table(vma, flags);

	if (is_hugepd(__hugepd(p4d_val(*p4d)))) {
		page = follow_huge_pd(vma, address,
				      __hugepd(p4d_val(*p4d)), flags,
				      P4D_SHIFT);
		if (page)
			return page;
		return no_page_table(vma, flags);
	}
	return follow_pud_mask(vma, address, p4d, flags, page_mask);
}
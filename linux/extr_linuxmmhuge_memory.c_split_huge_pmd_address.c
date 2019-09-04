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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int /*<<< orphan*/  __split_huge_pmd (struct vm_area_struct*,int /*<<< orphan*/ *,unsigned long,int,struct page*) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  p4d_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 

void split_huge_pmd_address(struct vm_area_struct *vma, unsigned long address,
		bool freeze, struct page *page)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;

	pgd = pgd_offset(vma->vm_mm, address);
	if (!pgd_present(*pgd))
		return;

	p4d = p4d_offset(pgd, address);
	if (!p4d_present(*p4d))
		return;

	pud = pud_offset(p4d, address);
	if (!pud_present(*pud))
		return;

	pmd = pmd_offset(pud, address);

	__split_huge_pmd(vma, pmd, address, freeze, page);
}
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
struct vm_area_struct {int /*<<< orphan*/  vm_page_prot; } ;
struct page {int dummy; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgtable_t ;

/* Variables and functions */
 int /*<<< orphan*/  mk_pmd (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mm_inc_nr_ptes (struct mm_struct*) ; 
 int /*<<< orphan*/  pgtable_trans_huge_deposit (struct mm_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_mkhuge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pmd_at (struct mm_struct*,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool set_huge_zero_page(pgtable_t pgtable, struct mm_struct *mm,
		struct vm_area_struct *vma, unsigned long haddr, pmd_t *pmd,
		struct page *zero_page)
{
	pmd_t entry;
	if (!pmd_none(*pmd))
		return false;
	entry = mk_pmd(zero_page, vma->vm_page_prot);
	entry = pmd_mkhuge(entry);
	if (pgtable)
		pgtable_trans_huge_deposit(mm, pmd, pgtable);
	set_pmd_at(mm, haddr, pmd, entry);
	mm_inc_nr_ptes(mm);
	return true;
}
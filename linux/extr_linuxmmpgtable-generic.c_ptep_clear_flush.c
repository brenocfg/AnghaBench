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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  flush_tlb_page (struct vm_area_struct*,unsigned long) ; 
 scalar_t__ pte_accessible (struct mm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptep_get_and_clear (struct mm_struct*,unsigned long,int /*<<< orphan*/ *) ; 

pte_t ptep_clear_flush(struct vm_area_struct *vma, unsigned long address,
		       pte_t *ptep)
{
	struct mm_struct *mm = (vma)->vm_mm;
	pte_t pte;
	pte = ptep_get_and_clear(mm, address, ptep);
	if (pte_accessible(mm, pte))
		flush_tlb_page(vma, address);
	return pte;
}
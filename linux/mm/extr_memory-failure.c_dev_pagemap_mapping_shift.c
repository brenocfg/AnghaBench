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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long PMD_SHIFT ; 
 unsigned long PUD_SHIFT ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  p4d_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pmd_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pmd_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pte_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pte_offset_map (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_devmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pud_present (int /*<<< orphan*/ ) ; 
 unsigned long vma_address (struct page*,struct vm_area_struct*) ; 

__attribute__((used)) static unsigned long dev_pagemap_mapping_shift(struct page *page,
		struct vm_area_struct *vma)
{
	unsigned long address = vma_address(page, vma);
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte;

	pgd = pgd_offset(vma->vm_mm, address);
	if (!pgd_present(*pgd))
		return 0;
	p4d = p4d_offset(pgd, address);
	if (!p4d_present(*p4d))
		return 0;
	pud = pud_offset(p4d, address);
	if (!pud_present(*pud))
		return 0;
	if (pud_devmap(*pud))
		return PUD_SHIFT;
	pmd = pmd_offset(pud, address);
	if (!pmd_present(*pmd))
		return 0;
	if (pmd_devmap(*pmd))
		return PMD_SHIFT;
	pte = pte_offset_map(pmd, address);
	if (!pte_present(*pte))
		return 0;
	if (pte_devmap(*pte))
		return PAGE_SHIFT;
	return 0;
}
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
struct vm_area_struct {unsigned long vm_start; scalar_t__ vm_end; struct vm_area_struct* vm_next; } ;
struct mmu_gather {int dummy; } ;

/* Variables and functions */
 scalar_t__ PMD_SIZE ; 
 int /*<<< orphan*/  free_pgd_range (struct mmu_gather*,unsigned long,scalar_t__,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  hugetlb_free_pgd_range (struct mmu_gather*,unsigned long,scalar_t__,unsigned long,unsigned long) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int /*<<< orphan*/  unlink_anon_vmas (struct vm_area_struct*) ; 
 int /*<<< orphan*/  unlink_file_vma (struct vm_area_struct*) ; 

void free_pgtables(struct mmu_gather *tlb, struct vm_area_struct *vma,
		unsigned long floor, unsigned long ceiling)
{
	while (vma) {
		struct vm_area_struct *next = vma->vm_next;
		unsigned long addr = vma->vm_start;

		/*
		 * Hide vma from rmap and truncate_pagecache before freeing
		 * pgtables
		 */
		unlink_anon_vmas(vma);
		unlink_file_vma(vma);

		if (is_vm_hugetlb_page(vma)) {
			hugetlb_free_pgd_range(tlb, addr, vma->vm_end,
				floor, next ? next->vm_start : ceiling);
		} else {
			/*
			 * Optimization: gather nearby vmas into one call down
			 */
			while (next && next->vm_start <= vma->vm_end + PMD_SIZE
			       && !is_vm_hugetlb_page(next)) {
				vma = next;
				next = vma->vm_next;
				unlink_anon_vmas(vma);
				unlink_file_vma(vma);
			}
			free_pgd_range(tlb, addr, vma->vm_end,
				floor, next ? next->vm_start : ceiling);
		}
		vma = next;
	}
}
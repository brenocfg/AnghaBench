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
struct vm_area_struct {int vm_flags; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int VM_ACCOUNT ; 
 struct vm_area_struct* remove_vma (struct vm_area_struct*) ; 
 int /*<<< orphan*/  update_hiwater_vm (struct mm_struct*) ; 
 int /*<<< orphan*/  validate_mm (struct mm_struct*) ; 
 int /*<<< orphan*/  vm_stat_account (struct mm_struct*,int,long) ; 
 int /*<<< orphan*/  vm_unacct_memory (unsigned long) ; 
 long vma_pages (struct vm_area_struct*) ; 

__attribute__((used)) static void remove_vma_list(struct mm_struct *mm, struct vm_area_struct *vma)
{
	unsigned long nr_accounted = 0;

	/* Update high watermark before we lower total_vm */
	update_hiwater_vm(mm);
	do {
		long nrpages = vma_pages(vma);

		if (vma->vm_flags & VM_ACCOUNT)
			nr_accounted += nrpages;
		vm_stat_account(mm, vma->vm_flags, -nrpages);
		vma = remove_vma(vma);
	} while (vma);
	vm_unacct_memory(nr_accounted);
	validate_mm(mm);
}
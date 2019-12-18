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
struct vm_area_struct {unsigned long vm_end; } ;

/* Variables and functions */
 unsigned long HPAGE_PMD_MASK ; 
 unsigned long HPAGE_PMD_SIZE ; 
 int __transparent_hugepage_enabled (struct vm_area_struct*) ; 
 int shmem_huge_enabled (struct vm_area_struct*) ; 
 int /*<<< orphan*/  transhuge_vma_suitable (struct vm_area_struct*,unsigned long) ; 
 scalar_t__ vma_is_anonymous (struct vm_area_struct*) ; 
 scalar_t__ vma_is_shmem (struct vm_area_struct*) ; 

bool transparent_hugepage_enabled(struct vm_area_struct *vma)
{
	/* The addr is used to check if the vma size fits */
	unsigned long addr = (vma->vm_end & HPAGE_PMD_MASK) - HPAGE_PMD_SIZE;

	if (!transhuge_vma_suitable(vma, addr))
		return false;
	if (vma_is_anonymous(vma))
		return __transparent_hugepage_enabled(vma);
	if (vma_is_shmem(vma))
		return shmem_huge_enabled(vma);

	return false;
}
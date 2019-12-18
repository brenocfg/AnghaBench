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
struct resv_map {int dummy; } ;

/* Variables and functions */
 unsigned long HPAGE_RESV_MASK ; 
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 int VM_MAYSHARE ; 
 unsigned long get_vma_private_data (struct vm_area_struct*) ; 
 int /*<<< orphan*/  is_vm_hugetlb_page (struct vm_area_struct*) ; 
 int /*<<< orphan*/  set_vma_private_data (struct vm_area_struct*,unsigned long) ; 

__attribute__((used)) static void set_vma_resv_map(struct vm_area_struct *vma, struct resv_map *map)
{
	VM_BUG_ON_VMA(!is_vm_hugetlb_page(vma), vma);
	VM_BUG_ON_VMA(vma->vm_flags & VM_MAYSHARE, vma);

	set_vma_private_data(vma, (get_vma_private_data(vma) &
				HPAGE_RESV_MASK) | (unsigned long)map);
}
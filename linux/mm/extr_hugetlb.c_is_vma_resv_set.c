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

/* Variables and functions */
 int /*<<< orphan*/  VM_BUG_ON_VMA (int,struct vm_area_struct*) ; 
 unsigned long get_vma_private_data (struct vm_area_struct*) ; 
 int /*<<< orphan*/  is_vm_hugetlb_page (struct vm_area_struct*) ; 

__attribute__((used)) static int is_vma_resv_set(struct vm_area_struct *vma, unsigned long flag)
{
	VM_BUG_ON_VMA(!is_vm_hugetlb_page(vma), vma);

	return (get_vma_private_data(vma) & flag) != 0;
}
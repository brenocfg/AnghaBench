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
 int EINVAL ; 
 int /*<<< orphan*/  hstate_vma (struct vm_area_struct*) ; 
 unsigned long huge_page_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hugetlb_vm_op_split(struct vm_area_struct *vma, unsigned long addr)
{
	if (addr & ~(huge_page_mask(hstate_vma(vma))))
		return -EINVAL;
	return 0;
}
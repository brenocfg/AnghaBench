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
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 unsigned long change_protection_range (struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/ ,int,int) ; 
 unsigned long hugetlb_change_protection (struct vm_area_struct*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ is_vm_hugetlb_page (struct vm_area_struct*) ; 

unsigned long change_protection(struct vm_area_struct *vma, unsigned long start,
		       unsigned long end, pgprot_t newprot,
		       int dirty_accountable, int prot_numa)
{
	unsigned long pages;

	if (is_vm_hugetlb_page(vma))
		pages = hugetlb_change_protection(vma, start, end, newprot);
	else
		pages = change_protection_range(vma, start, end, newprot, dirty_accountable, prot_numa);

	return pages;
}
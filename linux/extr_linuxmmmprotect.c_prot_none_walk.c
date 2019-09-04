#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {int dummy; } ;
struct mm_walk {int /*<<< orphan*/ * private; int /*<<< orphan*/  mm; int /*<<< orphan*/  test_walk; int /*<<< orphan*/  hugetlb_entry; int /*<<< orphan*/  pte_entry; } ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_2__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 TYPE_1__* current ; 
 int /*<<< orphan*/  prot_none_hugetlb_entry ; 
 int /*<<< orphan*/  prot_none_pte_entry ; 
 int /*<<< orphan*/  prot_none_test ; 
 int /*<<< orphan*/  vm_get_page_prot (unsigned long) ; 
 int walk_page_range (unsigned long,unsigned long,struct mm_walk*) ; 

__attribute__((used)) static int prot_none_walk(struct vm_area_struct *vma, unsigned long start,
			   unsigned long end, unsigned long newflags)
{
	pgprot_t new_pgprot = vm_get_page_prot(newflags);
	struct mm_walk prot_none_walk = {
		.pte_entry = prot_none_pte_entry,
		.hugetlb_entry = prot_none_hugetlb_entry,
		.test_walk = prot_none_test,
		.mm = current->mm,
		.private = &new_pgprot,
	};

	return walk_page_range(start, end, &prot_none_walk);
}
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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUMA_HINT_FAULTS ; 
 int /*<<< orphan*/  NUMA_HINT_FAULTS_LOCAL ; 
 int TNF_FAULT_LOCAL ; 
 int /*<<< orphan*/  count_vm_numa_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int mpol_misplaced (struct page*,struct vm_area_struct*,unsigned long) ; 
 int numa_node_id () ; 

__attribute__((used)) static int numa_migrate_prep(struct page *page, struct vm_area_struct *vma,
				unsigned long addr, int page_nid,
				int *flags)
{
	get_page(page);

	count_vm_numa_event(NUMA_HINT_FAULTS);
	if (page_nid == numa_node_id()) {
		count_vm_numa_event(NUMA_HINT_FAULTS_LOCAL);
		*flags |= TNF_FAULT_LOCAL;
	}

	return mpol_misplaced(page, vma, addr);
}
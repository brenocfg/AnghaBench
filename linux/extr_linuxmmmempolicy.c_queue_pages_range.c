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
struct queue_pages {unsigned long flags; int /*<<< orphan*/ * prev; int /*<<< orphan*/ * nmask; struct list_head* pagelist; } ;
struct mm_walk {struct queue_pages* private; struct mm_struct* mm; int /*<<< orphan*/  test_walk; int /*<<< orphan*/  pmd_entry; int /*<<< orphan*/  hugetlb_entry; } ;
struct mm_struct {int dummy; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int /*<<< orphan*/  queue_pages_hugetlb ; 
 int /*<<< orphan*/  queue_pages_pte_range ; 
 int /*<<< orphan*/  queue_pages_test_walk ; 
 int walk_page_range (unsigned long,unsigned long,struct mm_walk*) ; 

__attribute__((used)) static int
queue_pages_range(struct mm_struct *mm, unsigned long start, unsigned long end,
		nodemask_t *nodes, unsigned long flags,
		struct list_head *pagelist)
{
	struct queue_pages qp = {
		.pagelist = pagelist,
		.flags = flags,
		.nmask = nodes,
		.prev = NULL,
	};
	struct mm_walk queue_pages_walk = {
		.hugetlb_entry = queue_pages_hugetlb,
		.pmd_entry = queue_pages_pte_range,
		.test_walk = queue_pages_test_walk,
		.mm = mm,
		.private = &qp,
	};

	return walk_page_range(start, end, &queue_pages_walk);
}
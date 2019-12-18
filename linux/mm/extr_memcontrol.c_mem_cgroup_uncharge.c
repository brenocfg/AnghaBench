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
struct uncharge_gather {int dummy; } ;
struct page {int /*<<< orphan*/  mem_cgroup; } ;

/* Variables and functions */
 scalar_t__ mem_cgroup_disabled () ; 
 int /*<<< orphan*/  uncharge_batch (struct uncharge_gather*) ; 
 int /*<<< orphan*/  uncharge_gather_clear (struct uncharge_gather*) ; 
 int /*<<< orphan*/  uncharge_page (struct page*,struct uncharge_gather*) ; 

void mem_cgroup_uncharge(struct page *page)
{
	struct uncharge_gather ug;

	if (mem_cgroup_disabled())
		return;

	/* Don't touch page->lru of any random page, pre-check: */
	if (!page->mem_cgroup)
		return;

	uncharge_gather_clear(&ug);
	uncharge_page(page, &ug);
	uncharge_batch(&ug);
}
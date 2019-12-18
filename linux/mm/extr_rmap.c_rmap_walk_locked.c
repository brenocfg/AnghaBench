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
struct rmap_walk_control {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 scalar_t__ PageAnon (struct page*) ; 
 int /*<<< orphan*/  PageKsm (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int /*<<< orphan*/ ,struct page*) ; 
 int /*<<< orphan*/  rmap_walk_anon (struct page*,struct rmap_walk_control*,int) ; 
 int /*<<< orphan*/  rmap_walk_file (struct page*,struct rmap_walk_control*,int) ; 

void rmap_walk_locked(struct page *page, struct rmap_walk_control *rwc)
{
	/* no ksm support for now */
	VM_BUG_ON_PAGE(PageKsm(page), page);
	if (PageAnon(page))
		rmap_walk_anon(page, rwc, true);
	else
		rmap_walk_file(page, rwc, true);
}
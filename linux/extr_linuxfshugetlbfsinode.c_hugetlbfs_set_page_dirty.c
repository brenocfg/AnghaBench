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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SetPageDirty (struct page*) ; 
 struct page* compound_head (struct page*) ; 

__attribute__((used)) static int hugetlbfs_set_page_dirty(struct page *page)
{
	struct page *head = compound_head(page);

	SetPageDirty(head);
	return 0;
}
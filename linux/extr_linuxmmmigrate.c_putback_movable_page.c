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
struct page {int dummy; } ;
struct address_space {TYPE_1__* a_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* putback_page ) (struct page*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PageIsolated (struct page*) ; 
 int /*<<< orphan*/  PageLocked (struct page*) ; 
 int /*<<< orphan*/  PageMovable (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON_PAGE (int,struct page*) ; 
 int /*<<< orphan*/  __ClearPageIsolated (struct page*) ; 
 struct address_space* page_mapping (struct page*) ; 
 int /*<<< orphan*/  stub1 (struct page*) ; 

void putback_movable_page(struct page *page)
{
	struct address_space *mapping;

	VM_BUG_ON_PAGE(!PageLocked(page), page);
	VM_BUG_ON_PAGE(!PageMovable(page), page);
	VM_BUG_ON_PAGE(!PageIsolated(page), page);

	mapping = page_mapping(page);
	mapping->a_ops->putback_page(page);
	__ClearPageIsolated(page);
}
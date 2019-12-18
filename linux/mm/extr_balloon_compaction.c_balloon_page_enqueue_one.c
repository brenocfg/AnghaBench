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
struct balloon_dev_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BALLOON_INFLATE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __count_vm_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  balloon_page_insert (struct balloon_dev_info*,struct page*) ; 
 int /*<<< orphan*/  trylock_page (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static void balloon_page_enqueue_one(struct balloon_dev_info *b_dev_info,
				     struct page *page)
{
	/*
	 * Block others from accessing the 'page' when we get around to
	 * establishing additional references. We should be the only one
	 * holding a reference to the 'page' at this point. If we are not, then
	 * memory corruption is possible and we should stop execution.
	 */
	BUG_ON(!trylock_page(page));
	balloon_page_insert(b_dev_info, page);
	unlock_page(page);
	__count_vm_event(BALLOON_INFLATE);
}
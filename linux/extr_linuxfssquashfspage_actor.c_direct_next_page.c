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
struct squashfs_page_actor {void* pageaddr; scalar_t__ next_page; scalar_t__ pages; int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int /*<<< orphan*/ * kmap_atomic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap_atomic (void*) ; 

__attribute__((used)) static void *direct_next_page(struct squashfs_page_actor *actor)
{
	if (actor->pageaddr)
		kunmap_atomic(actor->pageaddr);

	return actor->pageaddr = actor->next_page == actor->pages ? NULL :
		kmap_atomic(actor->page[actor->next_page++]);
}
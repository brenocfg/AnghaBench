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
struct squashfs_page_actor {int length; void** buffer; int pages; int /*<<< orphan*/  squashfs_finish_page; int /*<<< orphan*/  squashfs_next_page; int /*<<< orphan*/  squashfs_first_page; scalar_t__ next_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  cache_finish_page ; 
 int /*<<< orphan*/  cache_first_page ; 
 int /*<<< orphan*/  cache_next_page ; 
 struct squashfs_page_actor* kmalloc (int,int /*<<< orphan*/ ) ; 

struct squashfs_page_actor *squashfs_page_actor_init(void **buffer,
	int pages, int length)
{
	struct squashfs_page_actor *actor = kmalloc(sizeof(*actor), GFP_KERNEL);

	if (actor == NULL)
		return NULL;

	actor->length = length ? : pages * PAGE_SIZE;
	actor->buffer = buffer;
	actor->pages = pages;
	actor->next_page = 0;
	actor->squashfs_first_page = cache_first_page;
	actor->squashfs_next_page = cache_next_page;
	actor->squashfs_finish_page = cache_finish_page;
	return actor;
}
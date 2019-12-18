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
struct linked_page {void* data; struct linked_page* next; } ;
struct chain_allocator {unsigned int used_space; struct linked_page* chain; int /*<<< orphan*/  gfp_mask; scalar_t__ safe_needed; } ;

/* Variables and functions */
 unsigned int LINKED_PAGE_DATA_SIZE ; 
 int /*<<< orphan*/  PG_ANY ; 
 struct linked_page* __get_safe_page (int /*<<< orphan*/ ) ; 
 struct linked_page* get_image_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *chain_alloc(struct chain_allocator *ca, unsigned int size)
{
	void *ret;

	if (LINKED_PAGE_DATA_SIZE - ca->used_space < size) {
		struct linked_page *lp;

		lp = ca->safe_needed ? __get_safe_page(ca->gfp_mask) :
					get_image_page(ca->gfp_mask, PG_ANY);
		if (!lp)
			return NULL;

		lp->next = ca->chain;
		ca->chain = lp;
		ca->used_space = 0;
	}
	ret = ca->chain->data + ca->used_space;
	ca->used_space += size;
	return ret;
}
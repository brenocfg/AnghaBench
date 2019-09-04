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
struct lru_cache {void* lc_slot; int nr_elements; int element_size; int /*<<< orphan*/  free; int /*<<< orphan*/  element_off; struct lc_element** lc_element; scalar_t__ flags; scalar_t__ pending_changes; scalar_t__ changed; scalar_t__ locked; scalar_t__ starving; scalar_t__ misses; scalar_t__ hits; scalar_t__ used; int /*<<< orphan*/  to_be_changed; int /*<<< orphan*/  lru; int /*<<< orphan*/  in_use; } ;
struct lc_element {unsigned int lc_index; int /*<<< orphan*/  list; void* lc_new_number; void* lc_number; } ;
struct hlist_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* LC_FREE ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

void lc_reset(struct lru_cache *lc)
{
	unsigned i;

	INIT_LIST_HEAD(&lc->in_use);
	INIT_LIST_HEAD(&lc->lru);
	INIT_LIST_HEAD(&lc->free);
	INIT_LIST_HEAD(&lc->to_be_changed);
	lc->used = 0;
	lc->hits = 0;
	lc->misses = 0;
	lc->starving = 0;
	lc->locked = 0;
	lc->changed = 0;
	lc->pending_changes = 0;
	lc->flags = 0;
	memset(lc->lc_slot, 0, sizeof(struct hlist_head) * lc->nr_elements);

	for (i = 0; i < lc->nr_elements; i++) {
		struct lc_element *e = lc->lc_element[i];
		void *p = e;
		p -= lc->element_off;
		memset(p, 0, lc->element_size);
		/* re-init it */
		e->lc_index = i;
		e->lc_number = LC_FREE;
		e->lc_new_number = LC_FREE;
		list_add(&e->list, &lc->free);
	}
}
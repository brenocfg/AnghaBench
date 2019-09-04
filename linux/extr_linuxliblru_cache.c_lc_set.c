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
struct list_head {int dummy; } ;
struct lru_cache {int nr_elements; struct list_head lru; struct list_head free; } ;
struct lc_element {unsigned int lc_number; unsigned int lc_new_number; scalar_t__ refcnt; int /*<<< orphan*/  list; int /*<<< orphan*/  colision; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int LC_FREE ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 struct lc_element* lc_element_by_index (struct lru_cache*,int) ; 
 int /*<<< orphan*/  lc_hash_slot (struct lru_cache*,unsigned int) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,struct list_head*) ; 

void lc_set(struct lru_cache *lc, unsigned int enr, int index)
{
	struct lc_element *e;
	struct list_head *lh;

	if (index < 0 || index >= lc->nr_elements)
		return;

	e = lc_element_by_index(lc, index);
	BUG_ON(e->lc_number != e->lc_new_number);
	BUG_ON(e->refcnt != 0);

	e->lc_number = e->lc_new_number = enr;
	hlist_del_init(&e->colision);
	if (enr == LC_FREE)
		lh = &lc->free;
	else {
		hlist_add_head(&e->colision, lc_hash_slot(lc, enr));
		lh = &lc->lru;
	}
	list_move(&e->list, lh);
}
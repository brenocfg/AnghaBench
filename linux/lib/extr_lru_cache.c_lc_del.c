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
struct lru_cache {int /*<<< orphan*/  free; } ;
struct lc_element {int /*<<< orphan*/  list; int /*<<< orphan*/  colision; int /*<<< orphan*/  lc_new_number; int /*<<< orphan*/  lc_number; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LC_FREE ; 
 int /*<<< orphan*/  PARANOIA_ENTRY () ; 
 int /*<<< orphan*/  PARANOIA_LC_ELEMENT (struct lru_cache*,struct lc_element*) ; 
 int /*<<< orphan*/  RETURN () ; 
 int /*<<< orphan*/  hlist_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void lc_del(struct lru_cache *lc, struct lc_element *e)
{
	PARANOIA_ENTRY();
	PARANOIA_LC_ELEMENT(lc, e);
	BUG_ON(e->refcnt);

	e->lc_number = e->lc_new_number = LC_FREE;
	hlist_del_init(&e->colision);
	list_move(&e->list, &lc->free);
	RETURN();
}
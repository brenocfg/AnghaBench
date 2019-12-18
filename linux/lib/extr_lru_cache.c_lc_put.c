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
struct lru_cache {int /*<<< orphan*/  flags; int /*<<< orphan*/  used; int /*<<< orphan*/  lru; } ;
struct lc_element {scalar_t__ refcnt; scalar_t__ lc_number; scalar_t__ lc_new_number; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PARANOIA_ENTRY () ; 
 int /*<<< orphan*/  PARANOIA_LC_ELEMENT (struct lru_cache*,struct lc_element*) ; 
 int /*<<< orphan*/  RETURN (scalar_t__) ; 
 int /*<<< orphan*/  __LC_STARVING ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

unsigned int lc_put(struct lru_cache *lc, struct lc_element *e)
{
	PARANOIA_ENTRY();
	PARANOIA_LC_ELEMENT(lc, e);
	BUG_ON(e->refcnt == 0);
	BUG_ON(e->lc_number != e->lc_new_number);
	if (--e->refcnt == 0) {
		/* move it to the front of LRU. */
		list_move(&e->list, &lc->lru);
		lc->used--;
		clear_bit_unlock(__LC_STARVING, &lc->flags);
	}
	RETURN(e->refcnt);
}
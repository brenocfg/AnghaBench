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
struct lru_cache {int flags; scalar_t__ pending_changes; scalar_t__ max_pending_changes; int /*<<< orphan*/  used; int /*<<< orphan*/  locked; int /*<<< orphan*/  misses; int /*<<< orphan*/  in_use; int /*<<< orphan*/  hits; int /*<<< orphan*/  starving; } ;
struct lc_element {scalar_t__ lc_new_number; scalar_t__ lc_number; int refcnt; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int LC_GET_MAY_CHANGE ; 
 unsigned int LC_GET_MAY_USE_UNCOMMITTED ; 
 int LC_STARVING ; 
 int /*<<< orphan*/  PARANOIA_ENTRY () ; 
 int /*<<< orphan*/  RETURN (struct lc_element*) ; 
 int /*<<< orphan*/  __LC_DIRTY ; 
 int /*<<< orphan*/  __LC_LOCKED ; 
 int /*<<< orphan*/  __LC_STARVING ; 
 struct lc_element* __lc_find (struct lru_cache*,unsigned int,int) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int*) ; 
 struct lc_element* lc_prepare_for_change (struct lru_cache*,unsigned int) ; 
 int /*<<< orphan*/  lc_unused_element_available (struct lru_cache*) ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static struct lc_element *__lc_get(struct lru_cache *lc, unsigned int enr, unsigned int flags)
{
	struct lc_element *e;

	PARANOIA_ENTRY();
	if (lc->flags & LC_STARVING) {
		++lc->starving;
		RETURN(NULL);
	}

	e = __lc_find(lc, enr, 1);
	/* if lc_new_number != lc_number,
	 * this enr is currently being pulled in already,
	 * and will be available once the pending transaction
	 * has been committed. */
	if (e) {
		if (e->lc_new_number != e->lc_number) {
			/* It has been found above, but on the "to_be_changed"
			 * list, not yet committed.  Don't pull it in twice,
			 * wait for the transaction, then try again...
			 */
			if (!(flags & LC_GET_MAY_USE_UNCOMMITTED))
				RETURN(NULL);
			/* ... unless the caller is aware of the implications,
			 * probably preparing a cumulative transaction. */
			++e->refcnt;
			++lc->hits;
			RETURN(e);
		}
		/* else: lc_new_number == lc_number; a real hit. */
		++lc->hits;
		if (e->refcnt++ == 0)
			lc->used++;
		list_move(&e->list, &lc->in_use); /* Not evictable... */
		RETURN(e);
	}
	/* e == NULL */

	++lc->misses;
	if (!(flags & LC_GET_MAY_CHANGE))
		RETURN(NULL);

	/* To avoid races with lc_try_lock(), first, mark us dirty
	 * (using test_and_set_bit, as it implies memory barriers), ... */
	test_and_set_bit(__LC_DIRTY, &lc->flags);

	/* ... only then check if it is locked anyways. If lc_unlock clears
	 * the dirty bit again, that's not a problem, we will come here again.
	 */
	if (test_bit(__LC_LOCKED, &lc->flags)) {
		++lc->locked;
		RETURN(NULL);
	}

	/* In case there is nothing available and we can not kick out
	 * the LRU element, we have to wait ...
	 */
	if (!lc_unused_element_available(lc)) {
		__set_bit(__LC_STARVING, &lc->flags);
		RETURN(NULL);
	}

	/* It was not present in the active set.  We are going to recycle an
	 * unused (or even "free") element, but we won't accumulate more than
	 * max_pending_changes changes.  */
	if (lc->pending_changes >= lc->max_pending_changes)
		RETURN(NULL);

	e = lc_prepare_for_change(lc, enr);
	BUG_ON(!e);

	clear_bit(__LC_STARVING, &lc->flags);
	BUG_ON(++e->refcnt != 1);
	lc->used++;
	lc->pending_changes++;

	RETURN(e);
}
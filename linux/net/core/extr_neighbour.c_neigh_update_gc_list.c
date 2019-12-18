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
struct neighbour {int nud_state; int flags; TYPE_1__* tbl; int /*<<< orphan*/  lock; int /*<<< orphan*/  gc_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  gc_entries; int /*<<< orphan*/  gc_list; } ;

/* Variables and functions */
 int NTF_EXT_LEARNED ; 
 int NUD_PERMANENT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neigh_update_gc_list(struct neighbour *n)
{
	bool on_gc_list, exempt_from_gc;

	write_lock_bh(&n->tbl->lock);
	write_lock(&n->lock);

	/* remove from the gc list if new state is permanent or if neighbor
	 * is externally learned; otherwise entry should be on the gc list
	 */
	exempt_from_gc = n->nud_state & NUD_PERMANENT ||
			 n->flags & NTF_EXT_LEARNED;
	on_gc_list = !list_empty(&n->gc_list);

	if (exempt_from_gc && on_gc_list) {
		list_del_init(&n->gc_list);
		atomic_dec(&n->tbl->gc_entries);
	} else if (!exempt_from_gc && !on_gc_list) {
		/* add entries to the tail; cleaning removes from the front */
		list_add_tail(&n->gc_list, &n->tbl->gc_list);
		atomic_inc(&n->tbl->gc_entries);
	}

	write_unlock(&n->lock);
	write_unlock_bh(&n->tbl->lock);
}
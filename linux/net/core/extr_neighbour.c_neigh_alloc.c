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
struct net_device {scalar_t__ neigh_priv_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  hh_lock; } ;
struct neighbour {unsigned long updated; unsigned long used; int dead; int /*<<< orphan*/  gc_list; int /*<<< orphan*/  refcnt; struct neigh_table* tbl; int /*<<< orphan*/  timer; int /*<<< orphan*/  parms; TYPE_1__ hh; int /*<<< orphan*/  output; int /*<<< orphan*/  nud_state; int /*<<< orphan*/  ha_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  arp_queue; } ;
struct neigh_table {int gc_thresh3; int gc_thresh2; int /*<<< orphan*/  gc_entries; int /*<<< orphan*/  entries; int /*<<< orphan*/  parms; scalar_t__ entry_size; int /*<<< orphan*/  id; scalar_t__ last_flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NEIGH_CACHE_STAT_INC (struct neigh_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUD_NONE ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  allocs ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 struct neighbour* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_blackhole ; 
 int /*<<< orphan*/  neigh_forced_gc (struct neigh_table*) ; 
 int /*<<< orphan*/  neigh_parms_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_timer_handler ; 
 int /*<<< orphan*/  net_info_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seqlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_fulls ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct neighbour *neigh_alloc(struct neigh_table *tbl,
				     struct net_device *dev,
				     bool exempt_from_gc)
{
	struct neighbour *n = NULL;
	unsigned long now = jiffies;
	int entries;

	if (exempt_from_gc)
		goto do_alloc;

	entries = atomic_inc_return(&tbl->gc_entries) - 1;
	if (entries >= tbl->gc_thresh3 ||
	    (entries >= tbl->gc_thresh2 &&
	     time_after(now, tbl->last_flush + 5 * HZ))) {
		if (!neigh_forced_gc(tbl) &&
		    entries >= tbl->gc_thresh3) {
			net_info_ratelimited("%s: neighbor table overflow!\n",
					     tbl->id);
			NEIGH_CACHE_STAT_INC(tbl, table_fulls);
			goto out_entries;
		}
	}

do_alloc:
	n = kzalloc(tbl->entry_size + dev->neigh_priv_len, GFP_ATOMIC);
	if (!n)
		goto out_entries;

	__skb_queue_head_init(&n->arp_queue);
	rwlock_init(&n->lock);
	seqlock_init(&n->ha_lock);
	n->updated	  = n->used = now;
	n->nud_state	  = NUD_NONE;
	n->output	  = neigh_blackhole;
	seqlock_init(&n->hh.hh_lock);
	n->parms	  = neigh_parms_clone(&tbl->parms);
	timer_setup(&n->timer, neigh_timer_handler, 0);

	NEIGH_CACHE_STAT_INC(tbl, allocs);
	n->tbl		  = tbl;
	refcount_set(&n->refcnt, 1);
	n->dead		  = 1;
	INIT_LIST_HEAD(&n->gc_list);

	atomic_inc(&tbl->entries);
out:
	return n;

out_entries:
	if (!exempt_from_gc)
		atomic_dec(&tbl->gc_entries);
	goto out;
}
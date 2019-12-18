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
struct net_device {int dummy; } ;
struct neighbour {int /*<<< orphan*/  refcnt; } ;
struct neigh_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEIGH_CACHE_STAT_INC (struct neigh_table*,int /*<<< orphan*/ ) ; 
 struct neighbour* __neigh_lookup_noref (struct neigh_table*,void const*,struct net_device*) ; 
 int /*<<< orphan*/  hits ; 
 int /*<<< orphan*/  lookups ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

struct neighbour *neigh_lookup(struct neigh_table *tbl, const void *pkey,
			       struct net_device *dev)
{
	struct neighbour *n;

	NEIGH_CACHE_STAT_INC(tbl, lookups);

	rcu_read_lock_bh();
	n = __neigh_lookup_noref(tbl, pkey, dev);
	if (n) {
		if (!refcount_inc_not_zero(&n->refcnt))
			n = NULL;
		NEIGH_CACHE_STAT_INC(tbl, hits);
	}

	rcu_read_unlock_bh();
	return n;
}
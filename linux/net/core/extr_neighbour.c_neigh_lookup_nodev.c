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
typedef  size_t u32 ;
struct net {int dummy; } ;
struct neighbour {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  dev; int /*<<< orphan*/  primary_key; int /*<<< orphan*/  next; } ;
struct neigh_table {unsigned int key_len; int (* hash ) (void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  nht; } ;
struct neigh_hash_table {int hash_shift; int /*<<< orphan*/ * hash_buckets; int /*<<< orphan*/  hash_rnd; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEIGH_CACHE_STAT_INC (struct neigh_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hits ; 
 int /*<<< orphan*/  lookups ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,void const*,unsigned int) ; 
 scalar_t__ net_eq (int /*<<< orphan*/ ,struct net*) ; 
 void* rcu_dereference_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock_bh () ; 
 int /*<<< orphan*/  rcu_read_unlock_bh () ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 
 int stub1 (void const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct neighbour *neigh_lookup_nodev(struct neigh_table *tbl, struct net *net,
				     const void *pkey)
{
	struct neighbour *n;
	unsigned int key_len = tbl->key_len;
	u32 hash_val;
	struct neigh_hash_table *nht;

	NEIGH_CACHE_STAT_INC(tbl, lookups);

	rcu_read_lock_bh();
	nht = rcu_dereference_bh(tbl->nht);
	hash_val = tbl->hash(pkey, NULL, nht->hash_rnd) >> (32 - nht->hash_shift);

	for (n = rcu_dereference_bh(nht->hash_buckets[hash_val]);
	     n != NULL;
	     n = rcu_dereference_bh(n->next)) {
		if (!memcmp(n->primary_key, pkey, key_len) &&
		    net_eq(dev_net(n->dev), net)) {
			if (!refcount_inc_not_zero(&n->refcnt))
				n = NULL;
			NEIGH_CACHE_STAT_INC(tbl, hits);
			break;
		}
	}

	rcu_read_unlock_bh();
	return n;
}
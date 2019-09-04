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
struct neighbour {int hash_shift; int /*<<< orphan*/  rcu; int /*<<< orphan*/ * hash_buckets; int /*<<< orphan*/  next; int /*<<< orphan*/  hash_rnd; int /*<<< orphan*/  dev; int /*<<< orphan*/  primary_key; } ;
struct neigh_table {unsigned int (* hash ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  nht; int /*<<< orphan*/  lock; } ;
struct neigh_hash_table {int hash_shift; int /*<<< orphan*/  rcu; int /*<<< orphan*/ * hash_buckets; int /*<<< orphan*/  next; int /*<<< orphan*/  hash_rnd; int /*<<< orphan*/  dev; int /*<<< orphan*/  primary_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEIGH_CACHE_STAT_INC (struct neigh_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_grows ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct neighbour* neigh_hash_alloc (unsigned long) ; 
 int /*<<< orphan*/  neigh_hash_free_rcu ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct neighbour*) ; 
 struct neighbour* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct neigh_hash_table *neigh_hash_grow(struct neigh_table *tbl,
						unsigned long new_shift)
{
	unsigned int i, hash;
	struct neigh_hash_table *new_nht, *old_nht;

	NEIGH_CACHE_STAT_INC(tbl, hash_grows);

	old_nht = rcu_dereference_protected(tbl->nht,
					    lockdep_is_held(&tbl->lock));
	new_nht = neigh_hash_alloc(new_shift);
	if (!new_nht)
		return old_nht;

	for (i = 0; i < (1 << old_nht->hash_shift); i++) {
		struct neighbour *n, *next;

		for (n = rcu_dereference_protected(old_nht->hash_buckets[i],
						   lockdep_is_held(&tbl->lock));
		     n != NULL;
		     n = next) {
			hash = tbl->hash(n->primary_key, n->dev,
					 new_nht->hash_rnd);

			hash >>= (32 - new_nht->hash_shift);
			next = rcu_dereference_protected(n->next,
						lockdep_is_held(&tbl->lock));

			rcu_assign_pointer(n->next,
					   rcu_dereference_protected(
						new_nht->hash_buckets[hash],
						lockdep_is_held(&tbl->lock)));
			rcu_assign_pointer(new_nht->hash_buckets[hash], n);
		}
	}

	rcu_assign_pointer(tbl->nht, new_nht);
	call_rcu(&old_nht->rcu, neigh_hash_free_rcu);
	return new_nht;
}
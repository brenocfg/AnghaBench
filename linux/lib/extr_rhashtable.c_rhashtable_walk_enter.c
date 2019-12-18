#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* tbl; int /*<<< orphan*/  list; } ;
struct rhashtable_iter {TYPE_1__ walker; scalar_t__ end_of_table; scalar_t__ skip; scalar_t__ slot; int /*<<< orphan*/ * p; struct rhashtable* ht; } ;
struct rhashtable {int /*<<< orphan*/  lock; int /*<<< orphan*/  tbl; } ;
struct TYPE_4__ {int /*<<< orphan*/  walkers; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 TYPE_2__* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void rhashtable_walk_enter(struct rhashtable *ht, struct rhashtable_iter *iter)
{
	iter->ht = ht;
	iter->p = NULL;
	iter->slot = 0;
	iter->skip = 0;
	iter->end_of_table = 0;

	spin_lock(&ht->lock);
	iter->walker.tbl =
		rcu_dereference_protected(ht->tbl, lockdep_is_held(&ht->lock));
	list_add(&iter->walker.list, &iter->walker.tbl->walkers);
	spin_unlock(&ht->lock);
}
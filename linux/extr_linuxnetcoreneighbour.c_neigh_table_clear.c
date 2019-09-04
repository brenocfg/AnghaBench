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
struct neigh_table {int /*<<< orphan*/ * stats; int /*<<< orphan*/  id; int /*<<< orphan*/ * phash_buckets; int /*<<< orphan*/ * nht; int /*<<< orphan*/  entries; int /*<<< orphan*/  proxy_queue; int /*<<< orphan*/  proxy_timer; int /*<<< orphan*/  gc_work; } ;
struct TYPE_4__ {int /*<<< orphan*/  proc_net_stat; } ;
struct TYPE_3__ {int /*<<< orphan*/  rcu; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 TYPE_2__ init_net ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_hash_free_rcu ; 
 int /*<<< orphan*/  neigh_ifdown (struct neigh_table*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** neigh_tables ; 
 int /*<<< orphan*/  pneigh_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 TYPE_1__* rcu_dereference_protected (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int neigh_table_clear(int index, struct neigh_table *tbl)
{
	neigh_tables[index] = NULL;
	/* It is not clean... Fix it to unload IPv6 module safely */
	cancel_delayed_work_sync(&tbl->gc_work);
	del_timer_sync(&tbl->proxy_timer);
	pneigh_queue_purge(&tbl->proxy_queue);
	neigh_ifdown(tbl, NULL);
	if (atomic_read(&tbl->entries))
		pr_crit("neighbour leakage\n");

	call_rcu(&rcu_dereference_protected(tbl->nht, 1)->rcu,
		 neigh_hash_free_rcu);
	tbl->nht = NULL;

	kfree(tbl->phash_buckets);
	tbl->phash_buckets = NULL;

	remove_proc_entry(tbl->id, init_net.proc_net_stat);

	free_percpu(tbl->stats);
	tbl->stats = NULL;

	return 0;
}
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
struct neigh_parms {int dead; int /*<<< orphan*/  rcu_head; scalar_t__ dev; int /*<<< orphan*/  list; } ;
struct neigh_table {int /*<<< orphan*/  lock; struct neigh_parms parms; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (scalar_t__) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_rcu_free_parms ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

void neigh_parms_release(struct neigh_table *tbl, struct neigh_parms *parms)
{
	if (!parms || parms == &tbl->parms)
		return;
	write_lock_bh(&tbl->lock);
	list_del(&parms->list);
	parms->dead = 1;
	write_unlock_bh(&tbl->lock);
	if (parms->dev)
		dev_put(parms->dev);
	call_rcu(&parms->rcu_head, neigh_rcu_free_parms);
}
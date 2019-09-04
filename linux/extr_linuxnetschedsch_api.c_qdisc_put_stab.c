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
struct qdisc_size_table {scalar_t__ refcnt; int /*<<< orphan*/  rcu; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  call_rcu_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stab_kfree_rcu ; 

void qdisc_put_stab(struct qdisc_size_table *tab)
{
	if (!tab)
		return;

	if (--tab->refcnt == 0) {
		list_del(&tab->list);
		call_rcu_bh(&tab->rcu, stab_kfree_rcu);
	}
}
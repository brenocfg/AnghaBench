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
struct nfnetlink_subsystem {size_t subsys_id; } ;
struct TYPE_2__ {int /*<<< orphan*/ * subsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  nfnl_lock (size_t) ; 
 int /*<<< orphan*/  nfnl_unlock (size_t) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 TYPE_1__* table ; 

int nfnetlink_subsys_unregister(const struct nfnetlink_subsystem *n)
{
	nfnl_lock(n->subsys_id);
	table[n->subsys_id].subsys = NULL;
	nfnl_unlock(n->subsys_id);
	synchronize_rcu();
	return 0;
}
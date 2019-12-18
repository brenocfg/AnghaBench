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
struct sel_netif {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct sel_netif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_head ; 
 int /*<<< orphan*/  sel_netif_total ; 

__attribute__((used)) static void sel_netif_destroy(struct sel_netif *netif)
{
	list_del_rcu(&netif->list);
	sel_netif_total--;
	kfree_rcu(netif, rcu_head);
}
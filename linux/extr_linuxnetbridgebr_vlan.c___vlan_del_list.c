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
struct net_bridge_vlan {int /*<<< orphan*/  vlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __vlan_del_list(struct net_bridge_vlan *v)
{
	list_del_rcu(&v->vlist);
}
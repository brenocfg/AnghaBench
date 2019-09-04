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
struct ipvl_addr {int /*<<< orphan*/  hlnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 

void ipvlan_ht_addr_del(struct ipvl_addr *addr)
{
	hlist_del_init_rcu(&addr->hlnode);
}
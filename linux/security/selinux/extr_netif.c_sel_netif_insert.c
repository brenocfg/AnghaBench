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
struct TYPE_2__ {int /*<<< orphan*/  ifindex; int /*<<< orphan*/  ns; } ;
struct sel_netif {int /*<<< orphan*/  list; TYPE_1__ nsec; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ SEL_NETIF_HASH_MAX ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sel_netif_hash ; 
 int sel_netif_hashfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sel_netif_total ; 

__attribute__((used)) static int sel_netif_insert(struct sel_netif *netif)
{
	int idx;

	if (sel_netif_total >= SEL_NETIF_HASH_MAX)
		return -ENOSPC;

	idx = sel_netif_hashfn(netif->nsec.ns, netif->nsec.ifindex);
	list_add_rcu(&netif->list, &sel_netif_hash[idx]);
	sel_netif_total++;

	return 0;
}
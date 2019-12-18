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
struct net {int dummy; } ;
struct ip_set_net {int /*<<< orphan*/  is_deleted; } ;
struct ip_set {int dummy; } ;
typedef  int /*<<< orphan*/  ip_set_id_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFNL_SUBSYS_IPSET ; 
 int /*<<< orphan*/  __ip_set_put (struct ip_set*) ; 
 struct ip_set* ip_set (struct ip_set_net*,int /*<<< orphan*/ ) ; 
 struct ip_set_net* ip_set_pernet (struct net*) ; 
 int /*<<< orphan*/  nfnl_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfnl_unlock (int /*<<< orphan*/ ) ; 

void
ip_set_nfnl_put(struct net *net, ip_set_id_t index)
{
	struct ip_set *set;
	struct ip_set_net *inst = ip_set_pernet(net);

	nfnl_lock(NFNL_SUBSYS_IPSET);
	if (!inst->is_deleted) { /* already deleted from ip_set_net_exit() */
		set = ip_set(inst, index);
		if (set)
			__ip_set_put(set);
	}
	nfnl_unlock(NFNL_SUBSYS_IPSET);
}
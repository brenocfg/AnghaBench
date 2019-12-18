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
struct tipc_net {scalar_t__ mon_threshold; } ;
struct tipc_monitor {scalar_t__ peer_cnt; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct tipc_net* tipc_net (struct net*) ; 

__attribute__((used)) static inline bool tipc_mon_is_active(struct net *net, struct tipc_monitor *mon)
{
	struct tipc_net *tn = tipc_net(net);

	return mon->peer_cnt > tn->mon_threshold;
}
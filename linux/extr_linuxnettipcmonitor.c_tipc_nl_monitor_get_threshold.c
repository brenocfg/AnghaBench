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
struct tipc_net {int mon_threshold; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct tipc_net* tipc_net (struct net*) ; 

int tipc_nl_monitor_get_threshold(struct net *net)
{
	struct tipc_net *tn = tipc_net(net);

	return tn->mon_threshold;
}
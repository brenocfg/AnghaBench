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
struct tipc_link {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOPROTOOPT ; 
 struct tipc_link* tipc_bc_sndlink (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_lock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_unlock (struct net*) ; 
 int /*<<< orphan*/  tipc_link_reset_stats (struct tipc_link*) ; 

int tipc_bclink_reset_stats(struct net *net)
{
	struct tipc_link *l = tipc_bc_sndlink(net);

	if (!l)
		return -ENOPROTOOPT;

	tipc_bcast_lock(net);
	tipc_link_reset_stats(l);
	tipc_bcast_unlock(net);
	return 0;
}
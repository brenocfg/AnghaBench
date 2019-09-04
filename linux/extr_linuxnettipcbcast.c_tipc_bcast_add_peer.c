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
struct sk_buff_head {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct tipc_link* tipc_bc_sndlink (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_lock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_unlock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcbase_calc_bc_threshold (struct net*) ; 
 int /*<<< orphan*/  tipc_bcbase_select_primary (struct net*) ; 
 int /*<<< orphan*/  tipc_link_add_bc_peer (struct tipc_link*,struct tipc_link*,struct sk_buff_head*) ; 

void tipc_bcast_add_peer(struct net *net, struct tipc_link *uc_l,
			 struct sk_buff_head *xmitq)
{
	struct tipc_link *snd_l = tipc_bc_sndlink(net);

	tipc_bcast_lock(net);
	tipc_link_add_bc_peer(snd_l, uc_l, xmitq);
	tipc_bcbase_select_primary(net);
	tipc_bcbase_calc_bc_threshold(net);
	tipc_bcast_unlock(net);
}
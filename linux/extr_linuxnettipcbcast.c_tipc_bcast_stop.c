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
struct tipc_net {int /*<<< orphan*/  bcl; int /*<<< orphan*/  bcbase; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct tipc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  synchronize_net () ; 
 int /*<<< orphan*/  tipc_net_id ; 

void tipc_bcast_stop(struct net *net)
{
	struct tipc_net *tn = net_generic(net, tipc_net_id);

	synchronize_net();
	kfree(tn->bcbase);
	kfree(tn->bcl);
}
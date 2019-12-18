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
typedef  int u32 ;
struct tipc_bc_base {int rc_ratio; int /*<<< orphan*/  rcast_support; int /*<<< orphan*/  bcast_support; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
 struct tipc_bc_base* tipc_bc_base (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_lock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_unlock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcbase_calc_bc_threshold (struct net*) ; 

__attribute__((used)) static int tipc_bc_link_set_broadcast_ratio(struct net *net, u32 bc_ratio)
{
	struct tipc_bc_base *bb = tipc_bc_base(net);

	if (!bb->bcast_support || !bb->rcast_support)
		return -ENOPROTOOPT;

	if (bc_ratio > 100 || bc_ratio <= 0)
		return -EINVAL;

	bb->rc_ratio = bc_ratio;
	tipc_bcast_lock(net);
	tipc_bcbase_calc_bc_threshold(net);
	tipc_bcast_unlock(net);

	return 0;
}
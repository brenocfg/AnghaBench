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
typedef  int /*<<< orphan*/  u32 ;
struct tipc_bc_base {int /*<<< orphan*/  rc_ratio; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct tipc_bc_base* tipc_bc_base (struct net*) ; 

u32 tipc_bcast_get_broadcast_ratio(struct net *net)
{
	struct tipc_bc_base *bb = tipc_bc_base(net);

	return bb->rc_ratio;
}
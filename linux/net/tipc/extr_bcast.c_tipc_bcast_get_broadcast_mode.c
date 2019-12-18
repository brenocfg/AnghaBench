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
struct tipc_bc_base {scalar_t__ rcast_support; scalar_t__ bcast_support; scalar_t__ force_rcast; scalar_t__ force_bcast; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCLINK_MODE_BCAST ; 
 int /*<<< orphan*/  BCLINK_MODE_RCAST ; 
 int /*<<< orphan*/  BCLINK_MODE_SEL ; 
 struct tipc_bc_base* tipc_bc_base (struct net*) ; 

u32 tipc_bcast_get_broadcast_mode(struct net *net)
{
	struct tipc_bc_base *bb = tipc_bc_base(net);

	if (bb->force_bcast)
		return BCLINK_MODE_BCAST;

	if (bb->force_rcast)
		return BCLINK_MODE_RCAST;

	if (bb->bcast_support && bb->rcast_support)
		return BCLINK_MODE_SEL;

	return 0;
}
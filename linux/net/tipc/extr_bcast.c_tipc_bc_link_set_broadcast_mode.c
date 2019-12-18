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
struct tipc_bc_base {int force_bcast; int force_rcast; int /*<<< orphan*/  rcast_support; int /*<<< orphan*/  bcast_support; } ;
struct net {int dummy; } ;

/* Variables and functions */
#define  BCLINK_MODE_BCAST 130 
#define  BCLINK_MODE_RCAST 129 
#define  BCLINK_MODE_SEL 128 
 int EINVAL ; 
 int ENOPROTOOPT ; 
 struct tipc_bc_base* tipc_bc_base (struct net*) ; 

__attribute__((used)) static int tipc_bc_link_set_broadcast_mode(struct net *net, u32 bc_mode)
{
	struct tipc_bc_base *bb = tipc_bc_base(net);

	switch (bc_mode) {
	case BCLINK_MODE_BCAST:
		if (!bb->bcast_support)
			return -ENOPROTOOPT;

		bb->force_bcast = true;
		bb->force_rcast = false;
		break;
	case BCLINK_MODE_RCAST:
		if (!bb->rcast_support)
			return -ENOPROTOOPT;

		bb->force_bcast = false;
		bb->force_rcast = true;
		break;
	case BCLINK_MODE_SEL:
		if (!bb->bcast_support || !bb->rcast_support)
			return -ENOPROTOOPT;

		bb->force_bcast = false;
		bb->force_rcast = false;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
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
struct tipc_link {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCLINK_WIN_MIN ; 
 int EINVAL ; 
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  TIPC_MAX_LINK_WIN ; 
 struct tipc_link* tipc_bc_sndlink (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_lock (struct net*) ; 
 int /*<<< orphan*/  tipc_bcast_unlock (struct net*) ; 
 int /*<<< orphan*/  tipc_link_set_queue_limits (struct tipc_link*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tipc_bc_link_set_queue_limits(struct net *net, u32 limit)
{
	struct tipc_link *l = tipc_bc_sndlink(net);

	if (!l)
		return -ENOPROTOOPT;
	if (limit < BCLINK_WIN_MIN)
		limit = BCLINK_WIN_MIN;
	if (limit > TIPC_MAX_LINK_WIN)
		return -EINVAL;
	tipc_bcast_lock(net);
	tipc_link_set_queue_limits(l, limit);
	tipc_bcast_unlock(net);
	return 0;
}
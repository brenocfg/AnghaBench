#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tipc_mc_method {unsigned long expires; int rcast; scalar_t__ mandatory; } ;
struct tipc_bc_base {int bc_threshold; scalar_t__ force_rcast; scalar_t__ force_bcast; int /*<<< orphan*/  rcast_support; int /*<<< orphan*/  bcast_support; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int capabilities; } ;

/* Variables and functions */
 int TIPC_MCAST_RBCTL ; 
 unsigned long TIPC_METHOD_EXPIRE ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 struct tipc_bc_base* tipc_bc_base (struct net*) ; 
 TYPE_1__* tipc_net (struct net*) ; 

__attribute__((used)) static void tipc_bcast_select_xmit_method(struct net *net, int dests,
					  struct tipc_mc_method *method)
{
	struct tipc_bc_base *bb = tipc_bc_base(net);
	unsigned long exp = method->expires;

	/* Broadcast supported by used bearer/bearers? */
	if (!bb->bcast_support) {
		method->rcast = true;
		return;
	}
	/* Any destinations which don't support replicast ? */
	if (!bb->rcast_support) {
		method->rcast = false;
		return;
	}
	/* Can current method be changed ? */
	method->expires = jiffies + TIPC_METHOD_EXPIRE;
	if (method->mandatory)
		return;

	if (!(tipc_net(net)->capabilities & TIPC_MCAST_RBCTL) &&
	    time_before(jiffies, exp))
		return;

	/* Configuration as force 'broadcast' method */
	if (bb->force_bcast) {
		method->rcast = false;
		return;
	}
	/* Configuration as force 'replicast' method */
	if (bb->force_rcast) {
		method->rcast = true;
		return;
	}
	/* Configuration as 'autoselect' or default method */
	/* Determine method to use now */
	method->rcast = dests <= bb->bc_threshold;
}
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
struct tipc_mc_method {unsigned long expires; int rcast; scalar_t__ mandatory; } ;
struct tipc_bc_base {int bc_threshold; int /*<<< orphan*/  rcast_support; int /*<<< orphan*/  bcast_support; } ;
struct net {int dummy; } ;

/* Variables and functions */
 unsigned long TIPC_METHOD_EXPIRE ; 
 unsigned long jiffies ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 struct tipc_bc_base* tipc_bc_base (struct net*) ; 

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
	if (method->mandatory || time_before(jiffies, exp))
		return;

	/* Determine method to use now */
	method->rcast = dests <= bb->bc_threshold;
}
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
struct net_bridge_port {struct net_bridge* br; } ;
struct net_bridge {int dummy; } ;

/* Variables and functions */
 unsigned long BR_AUTO_MASK ; 
 unsigned long BR_NEIGH_SUPPRESS ; 
 int /*<<< orphan*/  br_recalculate_neigh_suppress_enabled (struct net_bridge*) ; 
 int /*<<< orphan*/  nbp_update_port_count (struct net_bridge*) ; 

void br_port_flags_change(struct net_bridge_port *p, unsigned long mask)
{
	struct net_bridge *br = p->br;

	if (mask & BR_AUTO_MASK)
		nbp_update_port_count(br);

	if (mask & BR_NEIGH_SUPPRESS)
		br_recalculate_neigh_suppress_enabled(br);
}
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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  addr_len; } ;
struct neighbour {int dummy; } ;
struct neigh_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEIGH_UPDATE_F_OVERRIDE ; 
 int /*<<< orphan*/  NUD_STALE ; 
 struct neighbour* __neigh_lookup (struct neigh_table*,void*,struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_update (struct neighbour*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct neighbour *neigh_event_ns(struct neigh_table *tbl,
				 u8 *lladdr, void *saddr,
				 struct net_device *dev)
{
	struct neighbour *neigh = __neigh_lookup(tbl, saddr, dev,
						 lladdr || !dev->addr_len);
	if (neigh)
		neigh_update(neigh, lladdr, NUD_STALE,
			     NEIGH_UPDATE_F_OVERRIDE, 0);
	return neigh;
}
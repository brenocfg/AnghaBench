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
struct net_device {int dummy; } ;
struct neighbour {int nud_state; } ;
struct neigh_table {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENXIO ; 
 int NEIGH_UPDATE_F_ADMIN ; 
 int NEIGH_UPDATE_F_OVERRIDE ; 
 int /*<<< orphan*/  NUD_FAILED ; 
 int NUD_NOARP ; 
 struct neigh_table arp_tbl ; 
 struct neighbour* neigh_lookup (struct neigh_table*,int /*<<< orphan*/ *,struct net_device*) ; 
 int /*<<< orphan*/  neigh_release (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_remove_one (struct neighbour*,struct neigh_table*) ; 
 int neigh_update (struct neighbour*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int arp_invalidate(struct net_device *dev, __be32 ip)
{
	struct neighbour *neigh = neigh_lookup(&arp_tbl, &ip, dev);
	int err = -ENXIO;
	struct neigh_table *tbl = &arp_tbl;

	if (neigh) {
		if (neigh->nud_state & ~NUD_NOARP)
			err = neigh_update(neigh, NULL, NUD_FAILED,
					   NEIGH_UPDATE_F_OVERRIDE|
					   NEIGH_UPDATE_F_ADMIN, 0);
		write_lock_bh(&tbl->lock);
		neigh_release(neigh);
		neigh_remove_one(neigh, tbl);
		write_unlock_bh(&tbl->lock);
	}

	return err;
}
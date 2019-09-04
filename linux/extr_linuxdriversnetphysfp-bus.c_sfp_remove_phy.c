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
struct sfp_upstream_ops {int /*<<< orphan*/  (* disconnect_phy ) (int /*<<< orphan*/ ) ;} ;
struct sfp_bus {int /*<<< orphan*/ * phydev; int /*<<< orphan*/  upstream; } ;

/* Variables and functions */
 struct sfp_upstream_ops* sfp_get_upstream_ops (struct sfp_bus*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void sfp_remove_phy(struct sfp_bus *bus)
{
	const struct sfp_upstream_ops *ops = sfp_get_upstream_ops(bus);

	if (ops && ops->disconnect_phy)
		ops->disconnect_phy(bus->upstream);
	bus->phydev = NULL;
}
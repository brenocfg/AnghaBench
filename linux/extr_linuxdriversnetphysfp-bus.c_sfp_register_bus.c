#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sfp_upstream_ops {int (* connect_phy ) (int /*<<< orphan*/ ,scalar_t__) ;int /*<<< orphan*/  (* link_down ) (int /*<<< orphan*/ ) ;} ;
struct sfp_bus {int registered; TYPE_2__* netdev; int /*<<< orphan*/  sfp; TYPE_1__* socket_ops; scalar_t__ started; scalar_t__ phydev; int /*<<< orphan*/  upstream; struct sfp_upstream_ops* upstream_ops; } ;
struct TYPE_4__ {struct sfp_bus* sfp_bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* start ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* attach ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sfp_register_bus(struct sfp_bus *bus)
{
	const struct sfp_upstream_ops *ops = bus->upstream_ops;
	int ret;

	if (ops) {
		if (ops->link_down)
			ops->link_down(bus->upstream);
		if (ops->connect_phy && bus->phydev) {
			ret = ops->connect_phy(bus->upstream, bus->phydev);
			if (ret)
				return ret;
		}
	}
	bus->socket_ops->attach(bus->sfp);
	if (bus->started)
		bus->socket_ops->start(bus->sfp);
	bus->netdev->sfp_bus = bus;
	bus->registered = true;
	return 0;
}
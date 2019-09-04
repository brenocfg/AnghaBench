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
struct mdio_mux_parent_bus {TYPE_1__* mii_bus; struct mdio_mux_child_bus* children; } ;
struct mdio_mux_child_bus {struct mdio_mux_child_bus* next; int /*<<< orphan*/  mii_bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void mdio_mux_uninit(void *mux_handle)
{
	struct mdio_mux_parent_bus *pb = mux_handle;
	struct mdio_mux_child_bus *cb = pb->children;

	while (cb) {
		mdiobus_unregister(cb->mii_bus);
		mdiobus_free(cb->mii_bus);
		cb = cb->next;
	}

	put_device(&pb->mii_bus->dev);
}
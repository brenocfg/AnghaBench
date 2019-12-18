#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fe_priv {TYPE_2__* mii_bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 

void fe_mdio_cleanup(struct fe_priv *priv)
{
	if (!priv->mii_bus)
		return;

	mdiobus_unregister(priv->mii_bus);
	of_node_put(priv->mii_bus->dev.of_node);
	kfree(priv->mii_bus);
}
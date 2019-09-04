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
struct ravb_private {int /*<<< orphan*/  mii_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_mdio_bitbang (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ravb_mdio_release(struct ravb_private *priv)
{
	/* Unregister mdio bus */
	mdiobus_unregister(priv->mii_bus);

	/* Free bitbang info */
	free_mdio_bitbang(priv->mii_bus);

	return 0;
}
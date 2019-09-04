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
struct platform_device {int dummy; } ;
struct mii_bus {struct hisi_femac_mdio_data* priv; } ;
struct hisi_femac_mdio_data {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 struct mii_bus* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int hisi_femac_mdio_remove(struct platform_device *pdev)
{
	struct mii_bus *bus = platform_get_drvdata(pdev);
	struct hisi_femac_mdio_data *data = bus->priv;

	mdiobus_unregister(bus);
	clk_disable_unprepare(data->clk);
	mdiobus_free(bus);

	return 0;
}
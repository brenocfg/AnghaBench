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
struct ag71xx_mdio {int /*<<< orphan*/  mdio_base; int /*<<< orphan*/  mii_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ag71xx_mdio*) ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 struct ag71xx_mdio* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ag71xx_mdio_remove(struct platform_device *pdev)
{
	struct ag71xx_mdio *am = platform_get_drvdata(pdev);

	if (am) {
		mdiobus_unregister(am->mii_bus);
		mdiobus_free(am->mii_bus);
		iounmap(am->mdio_base);
		kfree(am);
		platform_set_drvdata(pdev, NULL);
	}

	return 0;
}
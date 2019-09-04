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
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 struct mii_bus* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mscc_miim_remove(struct platform_device *pdev)
{
	struct mii_bus *bus = platform_get_drvdata(pdev);

	mdiobus_unregister(bus);

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpmac_driver ; 
 TYPE_1__* cpmac_mii ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mdiobus_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 

void cpmac_exit(void)
{
	platform_driver_unregister(&cpmac_driver);
	mdiobus_unregister(cpmac_mii);
	iounmap(cpmac_mii->priv);
	mdiobus_free(cpmac_mii);
}
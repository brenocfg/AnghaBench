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
struct dsa_switch {int /*<<< orphan*/ * devlink; TYPE_1__* ops; scalar_t__ slave_mii_bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* teardown ) (struct dsa_switch*) ;scalar_t__ phy_read; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_switch_unregister_notifier (struct dsa_switch*) ; 
 int /*<<< orphan*/  mdiobus_unregister (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct dsa_switch*) ; 

__attribute__((used)) static void dsa_switch_teardown(struct dsa_switch *ds)
{
	if (ds->slave_mii_bus && ds->ops->phy_read)
		mdiobus_unregister(ds->slave_mii_bus);

	dsa_switch_unregister_notifier(ds);

	if (ds->ops->teardown)
		ds->ops->teardown(ds);

	if (ds->devlink) {
		devlink_unregister(ds->devlink);
		devlink_free(ds->devlink);
		ds->devlink = NULL;
	}

}
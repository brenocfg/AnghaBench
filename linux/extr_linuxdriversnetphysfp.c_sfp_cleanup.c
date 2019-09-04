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
struct sfp {scalar_t__ i2c; scalar_t__ i2c_mii; int /*<<< orphan*/  timeout; int /*<<< orphan*/  poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_put_adapter (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct sfp*) ; 
 int /*<<< orphan*/  mdiobus_free (scalar_t__) ; 
 int /*<<< orphan*/  mdiobus_unregister (scalar_t__) ; 

__attribute__((used)) static void sfp_cleanup(void *data)
{
	struct sfp *sfp = data;

	cancel_delayed_work_sync(&sfp->poll);
	cancel_delayed_work_sync(&sfp->timeout);
	if (sfp->i2c_mii) {
		mdiobus_unregister(sfp->i2c_mii);
		mdiobus_free(sfp->i2c_mii);
	}
	if (sfp->i2c)
		i2c_put_adapter(sfp->i2c);
	kfree(sfp);
}
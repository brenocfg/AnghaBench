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
struct switchdev_trans {int ph_prepare; } ;
struct switchdev_obj {int /*<<< orphan*/  id; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __switchdev_port_obj_add (struct net_device*,struct switchdev_obj const*,struct switchdev_trans*) ; 
 int /*<<< orphan*/  switchdev_trans_init (struct switchdev_trans*) ; 
 int /*<<< orphan*/  switchdev_trans_items_destroy (struct switchdev_trans*) ; 
 int /*<<< orphan*/  switchdev_trans_items_warn_destroy (struct net_device*,struct switchdev_trans*) ; 

__attribute__((used)) static int switchdev_port_obj_add_now(struct net_device *dev,
				      const struct switchdev_obj *obj)
{
	struct switchdev_trans trans;
	int err;

	ASSERT_RTNL();

	switchdev_trans_init(&trans);

	/* Phase I: prepare for obj add. Driver/device should fail
	 * here if there are going to be issues in the commit phase,
	 * such as lack of resources or support.  The driver/device
	 * should reserve resources needed for the commit phase here,
	 * but should not commit the obj.
	 */

	trans.ph_prepare = true;
	err = __switchdev_port_obj_add(dev, obj, &trans);
	if (err) {
		/* Prepare phase failed: abort the transaction.  Any
		 * resources reserved in the prepare phase are
		 * released.
		 */

		if (err != -EOPNOTSUPP)
			switchdev_trans_items_destroy(&trans);

		return err;
	}

	/* Phase II: commit obj add.  This cannot fail as a fault
	 * of driver/device.  If it does, it's a bug in the driver/device
	 * because the driver said everythings was OK in phase I.
	 */

	trans.ph_prepare = false;
	err = __switchdev_port_obj_add(dev, obj, &trans);
	WARN(err, "%s: Commit of object (id=%d) failed.\n", dev->name, obj->id);
	switchdev_trans_items_warn_destroy(dev, &trans);

	return err;
}
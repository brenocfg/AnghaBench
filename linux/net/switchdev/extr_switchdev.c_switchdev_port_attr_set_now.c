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
struct switchdev_attr {int /*<<< orphan*/  id; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCHDEV_PORT_ATTR_SET ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int switchdev_port_attr_notify (int /*<<< orphan*/ ,struct net_device*,struct switchdev_attr const*,struct switchdev_trans*) ; 

__attribute__((used)) static int switchdev_port_attr_set_now(struct net_device *dev,
				       const struct switchdev_attr *attr)
{
	struct switchdev_trans trans;
	int err;

	/* Phase I: prepare for attr set. Driver/device should fail
	 * here if there are going to be issues in the commit phase,
	 * such as lack of resources or support.  The driver/device
	 * should reserve resources needed for the commit phase here,
	 * but should not commit the attr.
	 */

	trans.ph_prepare = true;
	err = switchdev_port_attr_notify(SWITCHDEV_PORT_ATTR_SET, dev, attr,
					 &trans);
	if (err)
		return err;

	/* Phase II: commit attr set.  This cannot fail as a fault
	 * of driver/device.  If it does, it's a bug in the driver/device
	 * because the driver said everythings was OK in phase I.
	 */

	trans.ph_prepare = false;
	err = switchdev_port_attr_notify(SWITCHDEV_PORT_ATTR_SET, dev, attr,
					 &trans);
	WARN(err, "%s: Commit of attribute (id=%d) failed.\n",
	     dev->name, attr->id);

	return err;
}
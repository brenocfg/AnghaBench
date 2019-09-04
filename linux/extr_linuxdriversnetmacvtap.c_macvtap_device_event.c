#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct net_device {int ifindex; TYPE_4__ dev; int /*<<< orphan*/ * rtnl_link_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  minor; } ;
struct macvtap_dev {TYPE_1__ tap; } ;
struct device {int /*<<< orphan*/  kobj; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int IFNAMSIZ ; 
 int /*<<< orphan*/  IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  NETDEV_CHANGE_TX_QUEUE_LEN 130 
#define  NETDEV_REGISTER 129 
#define  NETDEV_UNREGISTER 128 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int PTR_ERR (struct device*) ; 
 struct device* device_create (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macvtap_class ; 
 int /*<<< orphan*/  macvtap_link_ops ; 
 int /*<<< orphan*/  macvtap_major ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct macvtap_dev* netdev_priv (struct net_device*) ; 
 int notifier_from_errno (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int sysfs_create_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  tap_free_minor (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int tap_get_minor (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  tap_queue_resize (TYPE_1__*) ; 

__attribute__((used)) static int macvtap_device_event(struct notifier_block *unused,
				unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct macvtap_dev *vlantap;
	struct device *classdev;
	dev_t devt;
	int err;
	char tap_name[IFNAMSIZ];

	if (dev->rtnl_link_ops != &macvtap_link_ops)
		return NOTIFY_DONE;

	snprintf(tap_name, IFNAMSIZ, "tap%d", dev->ifindex);
	vlantap = netdev_priv(dev);

	switch (event) {
	case NETDEV_REGISTER:
		/* Create the device node here after the network device has
		 * been registered but before register_netdevice has
		 * finished running.
		 */
		err = tap_get_minor(macvtap_major, &vlantap->tap);
		if (err)
			return notifier_from_errno(err);

		devt = MKDEV(MAJOR(macvtap_major), vlantap->tap.minor);
		classdev = device_create(&macvtap_class, &dev->dev, devt,
					 dev, tap_name);
		if (IS_ERR(classdev)) {
			tap_free_minor(macvtap_major, &vlantap->tap);
			return notifier_from_errno(PTR_ERR(classdev));
		}
		err = sysfs_create_link(&dev->dev.kobj, &classdev->kobj,
					tap_name);
		if (err)
			return notifier_from_errno(err);
		break;
	case NETDEV_UNREGISTER:
		/* vlan->minor == 0 if NETDEV_REGISTER above failed */
		if (vlantap->tap.minor == 0)
			break;
		sysfs_remove_link(&dev->dev.kobj, tap_name);
		devt = MKDEV(MAJOR(macvtap_major), vlantap->tap.minor);
		device_destroy(&macvtap_class, devt);
		tap_free_minor(macvtap_major, &vlantap->tap);
		break;
	case NETDEV_CHANGE_TX_QUEUE_LEN:
		if (tap_queue_resize(&vlantap->tap))
			return NOTIFY_BAD;
		break;
	}

	return NOTIFY_DONE;
}
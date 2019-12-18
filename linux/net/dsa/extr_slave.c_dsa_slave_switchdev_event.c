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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;
struct dsa_switchdev_event_work {unsigned long event; int /*<<< orphan*/  work; struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
#define  SWITCHDEV_FDB_ADD_TO_DEVICE 129 
#define  SWITCHDEV_FDB_DEL_TO_DEVICE 128 
 unsigned long SWITCHDEV_PORT_ATTR_SET ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dsa_schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsa_slave_dev_check (struct net_device*) ; 
 int /*<<< orphan*/  dsa_slave_port_attr_set ; 
 int /*<<< orphan*/  dsa_slave_switchdev_event_work ; 
 int /*<<< orphan*/  dsa_slave_switchdev_fdb_work_init (struct dsa_switchdev_event_work*,void*) ; 
 int /*<<< orphan*/  kfree (struct dsa_switchdev_event_work*) ; 
 struct dsa_switchdev_event_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int notifier_from_errno (int) ; 
 int switchdev_handle_port_attr_set (struct net_device*,void*,int /*<<< orphan*/  (*) (struct net_device*),int /*<<< orphan*/ ) ; 
 struct net_device* switchdev_notifier_info_to_dev (void*) ; 

__attribute__((used)) static int dsa_slave_switchdev_event(struct notifier_block *unused,
				     unsigned long event, void *ptr)
{
	struct net_device *dev = switchdev_notifier_info_to_dev(ptr);
	struct dsa_switchdev_event_work *switchdev_work;
	int err;

	if (event == SWITCHDEV_PORT_ATTR_SET) {
		err = switchdev_handle_port_attr_set(dev, ptr,
						     dsa_slave_dev_check,
						     dsa_slave_port_attr_set);
		return notifier_from_errno(err);
	}

	if (!dsa_slave_dev_check(dev))
		return NOTIFY_DONE;

	switchdev_work = kzalloc(sizeof(*switchdev_work), GFP_ATOMIC);
	if (!switchdev_work)
		return NOTIFY_BAD;

	INIT_WORK(&switchdev_work->work,
		  dsa_slave_switchdev_event_work);
	switchdev_work->dev = dev;
	switchdev_work->event = event;

	switch (event) {
	case SWITCHDEV_FDB_ADD_TO_DEVICE: /* fall through */
	case SWITCHDEV_FDB_DEL_TO_DEVICE:
		if (dsa_slave_switchdev_fdb_work_init(switchdev_work, ptr))
			goto err_fdb_work_init;
		dev_hold(dev);
		break;
	default:
		kfree(switchdev_work);
		return NOTIFY_DONE;
	}

	dsa_schedule_work(&switchdev_work->work);
	return NOTIFY_OK;

err_fdb_work_init:
	kfree(switchdev_work);
	return NOTIFY_BAD;
}
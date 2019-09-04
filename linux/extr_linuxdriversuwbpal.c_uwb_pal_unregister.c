#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_6__ {TYPE_1__ dev; int /*<<< orphan*/  mutex; } ;
struct uwb_rc {TYPE_3__ uwb_dev; } ;
struct uwb_pal {char* name; TYPE_2__* device; int /*<<< orphan*/  debugfs_dir; int /*<<< orphan*/  node; struct uwb_rc* rc; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  uwb_radio_stop (struct uwb_pal*) ; 
 scalar_t__ uwb_rc_class_device_exists (struct uwb_rc*) ; 

void uwb_pal_unregister(struct uwb_pal *pal)
{
	struct uwb_rc *rc = pal->rc;

	uwb_radio_stop(pal);

	mutex_lock(&rc->uwb_dev.mutex);
	list_del(&pal->node);
	mutex_unlock(&rc->uwb_dev.mutex);

	debugfs_remove(pal->debugfs_dir);

	if (pal->device) {
		/* remove link to the PAL in the UWB device's directory. */
		if (uwb_rc_class_device_exists(rc))
			sysfs_remove_link(&rc->uwb_dev.dev.kobj, pal->name);

		/* remove link to uwb_rc in the PAL device's directory. */
		sysfs_remove_link(&pal->device->kobj, "uwb_rc");
	}
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct TYPE_4__ {struct kobject kobj; } ;
struct net_device {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct batadv_attribute {TYPE_2__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_SYSFS_IF_BAT_SUBDIR ; 
 int ENOMEM ; 
 struct batadv_attribute** batadv_batman_attrs ; 
 int /*<<< orphan*/  batadv_err (struct net_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct kobject* kobject_create_and_add (int /*<<< orphan*/ ,struct kobject*) ; 
 int sysfs_create_file (struct kobject*,TYPE_2__*) ; 
 int /*<<< orphan*/  sysfs_remove_file (struct kobject*,TYPE_2__*) ; 

int batadv_sysfs_add_hardif(struct kobject **hardif_obj, struct net_device *dev)
{
	struct kobject *hardif_kobject = &dev->dev.kobj;
	struct batadv_attribute **bat_attr;
	int err;

	*hardif_obj = kobject_create_and_add(BATADV_SYSFS_IF_BAT_SUBDIR,
					     hardif_kobject);

	if (!*hardif_obj) {
		batadv_err(dev, "Can't add sysfs directory: %s/%s\n", dev->name,
			   BATADV_SYSFS_IF_BAT_SUBDIR);
		goto out;
	}

	for (bat_attr = batadv_batman_attrs; *bat_attr; ++bat_attr) {
		err = sysfs_create_file(*hardif_obj, &((*bat_attr)->attr));
		if (err) {
			batadv_err(dev, "Can't add sysfs file: %s/%s/%s\n",
				   dev->name, BATADV_SYSFS_IF_BAT_SUBDIR,
				   ((*bat_attr)->attr).name);
			goto rem_attr;
		}
	}

	return 0;

rem_attr:
	for (bat_attr = batadv_batman_attrs; *bat_attr; ++bat_attr)
		sysfs_remove_file(*hardif_obj, &((*bat_attr)->attr));
out:
	return -ENOMEM;
}
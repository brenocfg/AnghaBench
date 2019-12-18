#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct list_head {int dummy; } ;
struct TYPE_3__ {struct list_head upper; } ;
struct net_device {TYPE_2__ dev; TYPE_1__ adj_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void netdev_adjacent_sysfs_del(struct net_device *dev,
			       char *name,
			       struct list_head *dev_list)
{
	char linkname[IFNAMSIZ+7];

	sprintf(linkname, dev_list == &dev->adj_list.upper ?
		"upper_%s" : "lower_%s", name);
	sysfs_remove_link(&(dev->dev.kobj), linkname);
}
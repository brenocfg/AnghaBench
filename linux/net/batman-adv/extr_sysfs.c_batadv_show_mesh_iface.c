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
struct net_device {int dummy; } ;
struct kobject {int dummy; } ;
struct batadv_hard_iface {scalar_t__ if_status; TYPE_1__* soft_iface; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 scalar_t__ BATADV_IF_NOT_IN_USE ; 
 struct batadv_hard_iface* batadv_hardif_get_by_netdev (struct net_device*) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 struct net_device* batadv_kobj_to_netdev (struct kobject*) ; 
 int /*<<< orphan*/  batadv_sysfs_deprecated (struct attribute*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 

__attribute__((used)) static ssize_t batadv_show_mesh_iface(struct kobject *kobj,
				      struct attribute *attr, char *buff)
{
	struct net_device *net_dev = batadv_kobj_to_netdev(kobj);
	struct batadv_hard_iface *hard_iface;
	ssize_t length;
	const char *ifname;

	batadv_sysfs_deprecated(attr);

	hard_iface = batadv_hardif_get_by_netdev(net_dev);
	if (!hard_iface)
		return 0;

	if (hard_iface->if_status == BATADV_IF_NOT_IN_USE)
		ifname =  "none";
	else
		ifname = hard_iface->soft_iface->name;

	length = sprintf(buff, "%s\n", ifname);

	batadv_hardif_put(hard_iface);

	return length;
}
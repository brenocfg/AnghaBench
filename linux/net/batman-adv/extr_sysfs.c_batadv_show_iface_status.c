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
struct net_device {int dummy; } ;
struct kobject {int dummy; } ;
struct batadv_hard_iface {int if_status; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
#define  BATADV_IF_ACTIVE 132 
#define  BATADV_IF_INACTIVE 131 
#define  BATADV_IF_NOT_IN_USE 130 
#define  BATADV_IF_TO_BE_ACTIVATED 129 
#define  BATADV_IF_TO_BE_REMOVED 128 
 struct batadv_hard_iface* batadv_hardif_get_by_netdev (struct net_device*) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 struct net_device* batadv_kobj_to_netdev (struct kobject*) ; 
 int /*<<< orphan*/  batadv_sysfs_deprecated (struct attribute*) ; 
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t batadv_show_iface_status(struct kobject *kobj,
					struct attribute *attr, char *buff)
{
	struct net_device *net_dev = batadv_kobj_to_netdev(kobj);
	struct batadv_hard_iface *hard_iface;
	ssize_t length;

	batadv_sysfs_deprecated(attr);

	hard_iface = batadv_hardif_get_by_netdev(net_dev);
	if (!hard_iface)
		return 0;

	switch (hard_iface->if_status) {
	case BATADV_IF_TO_BE_REMOVED:
		length = sprintf(buff, "disabling\n");
		break;
	case BATADV_IF_INACTIVE:
		length = sprintf(buff, "inactive\n");
		break;
	case BATADV_IF_ACTIVE:
		length = sprintf(buff, "active\n");
		break;
	case BATADV_IF_TO_BE_ACTIVATED:
		length = sprintf(buff, "enabling\n");
		break;
	case BATADV_IF_NOT_IN_USE:
	default:
		length = sprintf(buff, "not in use\n");
		break;
	}

	batadv_hardif_put(hard_iface);

	return length;
}
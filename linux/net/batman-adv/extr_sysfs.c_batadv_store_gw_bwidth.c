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
struct batadv_priv {int dummy; } ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_gw_bandwidth_set (struct net_device*,char*,size_t) ; 
 struct batadv_priv* batadv_kobj_to_batpriv (struct kobject*) ; 
 struct net_device* batadv_kobj_to_netdev (struct kobject*) ; 
 int /*<<< orphan*/  batadv_netlink_notify_mesh (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_sysfs_deprecated (struct attribute*) ; 

__attribute__((used)) static ssize_t batadv_store_gw_bwidth(struct kobject *kobj,
				      struct attribute *attr, char *buff,
				      size_t count)
{
	struct batadv_priv *bat_priv = batadv_kobj_to_batpriv(kobj);
	struct net_device *net_dev = batadv_kobj_to_netdev(kobj);
	ssize_t length;

	batadv_sysfs_deprecated(attr);

	if (buff[count - 1] == '\n')
		buff[count - 1] = '\0';

	length = batadv_gw_bandwidth_set(net_dev, buff, count);

	batadv_netlink_notify_mesh(bat_priv);

	return length;
}
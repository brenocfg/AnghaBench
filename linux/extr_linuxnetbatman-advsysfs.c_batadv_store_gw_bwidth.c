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
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_gw_bandwidth_set (struct net_device*,char*,size_t) ; 
 struct net_device* batadv_kobj_to_netdev (struct kobject*) ; 

__attribute__((used)) static ssize_t batadv_store_gw_bwidth(struct kobject *kobj,
				      struct attribute *attr, char *buff,
				      size_t count)
{
	struct net_device *net_dev = batadv_kobj_to_netdev(kobj);

	if (buff[count - 1] == '\n')
		buff[count - 1] = '\0';

	return batadv_gw_bandwidth_set(net_dev, buff, count);
}
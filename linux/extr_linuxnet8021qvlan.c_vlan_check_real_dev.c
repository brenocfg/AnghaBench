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
typedef  int /*<<< orphan*/  u16 ;
struct netlink_ext_ack {int dummy; } ;
struct net_device {char* name; int features; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int EEXIST ; 
 int EOPNOTSUPP ; 
 int NETIF_F_VLAN_CHALLENGED ; 
 int /*<<< orphan*/  NL_SET_ERR_MSG_MOD (struct netlink_ext_ack*,char*) ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 
 int /*<<< orphan*/ * vlan_find_dev (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vlan_check_real_dev(struct net_device *real_dev,
			__be16 protocol, u16 vlan_id,
			struct netlink_ext_ack *extack)
{
	const char *name = real_dev->name;

	if (real_dev->features & NETIF_F_VLAN_CHALLENGED) {
		pr_info("VLANs not supported on %s\n", name);
		NL_SET_ERR_MSG_MOD(extack, "VLANs not supported on device");
		return -EOPNOTSUPP;
	}

	if (vlan_find_dev(real_dev, protocol, vlan_id) != NULL) {
		NL_SET_ERR_MSG_MOD(extack, "VLAN device already exists");
		return -EEXIST;
	}

	return 0;
}
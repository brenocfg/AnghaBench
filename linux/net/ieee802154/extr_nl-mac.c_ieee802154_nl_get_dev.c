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
struct net_device {scalar_t__ type; } ;
struct genl_info {scalar_t__* attrs; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 scalar_t__ ARPHRD_IEEE802154 ; 
 size_t IEEE802154_ATTR_DEV_INDEX ; 
 size_t IEEE802154_ATTR_DEV_NAME ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 struct net_device* dev_get_by_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct net_device* dev_get_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  nla_get_u32 (scalar_t__) ; 
 int /*<<< orphan*/  nla_strlcpy (char*,scalar_t__,int) ; 

__attribute__((used)) static struct net_device *ieee802154_nl_get_dev(struct genl_info *info)
{
	struct net_device *dev;

	if (info->attrs[IEEE802154_ATTR_DEV_NAME]) {
		char name[IFNAMSIZ + 1];

		nla_strlcpy(name, info->attrs[IEEE802154_ATTR_DEV_NAME],
			    sizeof(name));
		dev = dev_get_by_name(&init_net, name);
	} else if (info->attrs[IEEE802154_ATTR_DEV_INDEX]) {
		dev = dev_get_by_index(&init_net,
			nla_get_u32(info->attrs[IEEE802154_ATTR_DEV_INDEX]));
	} else {
		return NULL;
	}

	if (!dev)
		return NULL;

	if (dev->type != ARPHRD_IEEE802154) {
		dev_put(dev);
		return NULL;
	}

	return dev;
}
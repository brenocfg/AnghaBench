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
struct wpan_dev {scalar_t__ iftype; struct net_device* lowpan_dev; } ;
struct sk_buff {int dummy; } ;
struct net_device {struct wpan_dev* ieee802154_ptr; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct net_device** user_ptr; } ;
struct cfg802154_registered_device {struct wpan_dev* ieee802154_ptr; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  IEEE802154_PAN_ID_BROADCAST ; 
 size_t NL802154_ATTR_PAN_ID ; 
 scalar_t__ NL802154_IFTYPE_MONITOR ; 
 scalar_t__ cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ nla_get_le16 (int /*<<< orphan*/ ) ; 
 int rdev_set_pan_id (struct net_device*,struct wpan_dev*,scalar_t__) ; 

__attribute__((used)) static int nl802154_set_pan_id(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg802154_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wpan_dev *wpan_dev = dev->ieee802154_ptr;
	__le16 pan_id;

	/* conflict here while tx/rx calls */
	if (netif_running(dev))
		return -EBUSY;

	if (wpan_dev->lowpan_dev) {
		if (netif_running(wpan_dev->lowpan_dev))
			return -EBUSY;
	}

	/* don't change address fields on monitor */
	if (wpan_dev->iftype == NL802154_IFTYPE_MONITOR ||
	    !info->attrs[NL802154_ATTR_PAN_ID])
		return -EINVAL;

	pan_id = nla_get_le16(info->attrs[NL802154_ATTR_PAN_ID]);

	/* TODO
	 * I am not sure about to check here on broadcast pan_id.
	 * Broadcast is a valid setting, comment from 802.15.4:
	 * If this value is 0xffff, the device is not associated.
	 *
	 * This could useful to simple deassociate an device.
	 */
	if (pan_id == cpu_to_le16(IEEE802154_PAN_ID_BROADCAST))
		return -EINVAL;

	return rdev_set_pan_id(rdev, wpan_dev, pan_id);
}
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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct genl_info {scalar_t__* attrs; } ;
struct TYPE_2__ {int (* scan_req ) (struct net_device*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 size_t IEEE802154_ATTR_CHANNELS ; 
 size_t IEEE802154_ATTR_DURATION ; 
 size_t IEEE802154_ATTR_PAGE ; 
 size_t IEEE802154_ATTR_SCAN_TYPE ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 TYPE_1__* ieee802154_mlme_ops (struct net_device*) ; 
 struct net_device* ieee802154_nl_get_dev (struct genl_info*) ; 
 int /*<<< orphan*/  nla_get_u32 (scalar_t__) ; 
 scalar_t__ nla_get_u8 (scalar_t__) ; 
 int stub1 (struct net_device*,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int ieee802154_scan_req(struct sk_buff *skb, struct genl_info *info)
{
	struct net_device *dev;
	int ret = -EOPNOTSUPP;
	u8 type;
	u32 channels;
	u8 duration;
	u8 page;

	if (!info->attrs[IEEE802154_ATTR_SCAN_TYPE] ||
	    !info->attrs[IEEE802154_ATTR_CHANNELS] ||
	    !info->attrs[IEEE802154_ATTR_DURATION])
		return -EINVAL;

	dev = ieee802154_nl_get_dev(info);
	if (!dev)
		return -ENODEV;
	if (!ieee802154_mlme_ops(dev)->scan_req)
		goto out;

	type = nla_get_u8(info->attrs[IEEE802154_ATTR_SCAN_TYPE]);
	channels = nla_get_u32(info->attrs[IEEE802154_ATTR_CHANNELS]);
	duration = nla_get_u8(info->attrs[IEEE802154_ATTR_DURATION]);

	if (info->attrs[IEEE802154_ATTR_PAGE])
		page = nla_get_u8(info->attrs[IEEE802154_ATTR_PAGE]);
	else
		page = 0;

	ret = ieee802154_mlme_ops(dev)->scan_req(dev, type, channels,
						 page, duration);

out:
	dev_put(dev);
	return ret;
}
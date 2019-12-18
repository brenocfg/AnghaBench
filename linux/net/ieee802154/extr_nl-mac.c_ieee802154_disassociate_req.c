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
struct sk_buff {int dummy; } ;
struct net_device {TYPE_1__* ieee802154_ptr; } ;
struct ieee802154_addr {int /*<<< orphan*/  pan_id; int /*<<< orphan*/  short_addr; int /*<<< orphan*/  mode; int /*<<< orphan*/  extended_addr; } ;
struct genl_info {scalar_t__* attrs; } ;
struct TYPE_4__ {int (* disassoc_req ) (struct net_device*,struct ieee802154_addr*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  pan_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IEEE802154_ADDR_LONG ; 
 int /*<<< orphan*/  IEEE802154_ADDR_SHORT ; 
 size_t IEEE802154_ATTR_DEST_HW_ADDR ; 
 size_t IEEE802154_ATTR_DEST_SHORT_ADDR ; 
 size_t IEEE802154_ATTR_REASON ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 TYPE_2__* ieee802154_mlme_ops (struct net_device*) ; 
 struct net_device* ieee802154_nl_get_dev (struct genl_info*) ; 
 int /*<<< orphan*/  nla_get_hwaddr (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_shortaddr (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u8 (scalar_t__) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int stub1 (struct net_device*,struct ieee802154_addr*,int /*<<< orphan*/ ) ; 

int ieee802154_disassociate_req(struct sk_buff *skb, struct genl_info *info)
{
	struct net_device *dev;
	struct ieee802154_addr addr;
	int ret = -EOPNOTSUPP;

	if ((!info->attrs[IEEE802154_ATTR_DEST_HW_ADDR] &&
	    !info->attrs[IEEE802154_ATTR_DEST_SHORT_ADDR]) ||
	    !info->attrs[IEEE802154_ATTR_REASON])
		return -EINVAL;

	dev = ieee802154_nl_get_dev(info);
	if (!dev)
		return -ENODEV;
	if (!ieee802154_mlme_ops(dev)->disassoc_req)
		goto out;

	if (info->attrs[IEEE802154_ATTR_DEST_HW_ADDR]) {
		addr.mode = IEEE802154_ADDR_LONG;
		addr.extended_addr = nla_get_hwaddr(
				info->attrs[IEEE802154_ATTR_DEST_HW_ADDR]);
	} else {
		addr.mode = IEEE802154_ADDR_SHORT;
		addr.short_addr = nla_get_shortaddr(
				info->attrs[IEEE802154_ATTR_DEST_SHORT_ADDR]);
	}
	rtnl_lock();
	addr.pan_id = dev->ieee802154_ptr->pan_id;
	rtnl_unlock();

	ret = ieee802154_mlme_ops(dev)->disassoc_req(dev, &addr,
			nla_get_u8(info->attrs[IEEE802154_ATTR_REASON]));

out:
	dev_put(dev);
	return ret;
}
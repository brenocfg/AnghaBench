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
typedef  scalar_t__ u8 ;
struct wpan_dev {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {scalar_t__ min_csma_backoffs; scalar_t__ max_csma_backoffs; } ;
struct TYPE_4__ {TYPE_1__ supported; } ;
struct net_device {TYPE_2__ wpan_phy; struct wpan_dev* ieee802154_ptr; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct net_device** user_ptr; } ;
struct cfg802154_registered_device {TYPE_2__ wpan_phy; struct wpan_dev* ieee802154_ptr; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 size_t NL802154_ATTR_MAX_CSMA_BACKOFFS ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ nla_get_u8 (int /*<<< orphan*/ ) ; 
 int rdev_set_max_csma_backoffs (struct net_device*,struct wpan_dev*,scalar_t__) ; 

__attribute__((used)) static int
nl802154_set_max_csma_backoffs(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg802154_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wpan_dev *wpan_dev = dev->ieee802154_ptr;
	u8 max_csma_backoffs;

	/* conflict here while other running iface settings */
	if (netif_running(dev))
		return -EBUSY;

	if (!info->attrs[NL802154_ATTR_MAX_CSMA_BACKOFFS])
		return -EINVAL;

	max_csma_backoffs = nla_get_u8(
			info->attrs[NL802154_ATTR_MAX_CSMA_BACKOFFS]);

	/* check 802.15.4 constraints */
	if (max_csma_backoffs < rdev->wpan_phy.supported.min_csma_backoffs ||
	    max_csma_backoffs > rdev->wpan_phy.supported.max_csma_backoffs)
		return -EINVAL;

	return rdev_set_max_csma_backoffs(rdev, wpan_dev, max_csma_backoffs);
}
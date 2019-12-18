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
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct cfg802154_registered_device** user_ptr; } ;
struct TYPE_3__ {int* channels; } ;
struct TYPE_4__ {TYPE_1__ supported; } ;
struct cfg802154_registered_device {TYPE_2__ wpan_phy; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ IEEE802154_MAX_CHANNEL ; 
 scalar_t__ IEEE802154_MAX_PAGE ; 
 size_t NL802154_ATTR_CHANNEL ; 
 size_t NL802154_ATTR_PAGE ; 
 scalar_t__ nla_get_u8 (int /*<<< orphan*/ ) ; 
 int rdev_set_channel (struct cfg802154_registered_device*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int nl802154_set_channel(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg802154_registered_device *rdev = info->user_ptr[0];
	u8 channel, page;

	if (!info->attrs[NL802154_ATTR_PAGE] ||
	    !info->attrs[NL802154_ATTR_CHANNEL])
		return -EINVAL;

	page = nla_get_u8(info->attrs[NL802154_ATTR_PAGE]);
	channel = nla_get_u8(info->attrs[NL802154_ATTR_CHANNEL]);

	/* check 802.15.4 constraints */
	if (page > IEEE802154_MAX_PAGE || channel > IEEE802154_MAX_CHANNEL ||
	    !(rdev->wpan_phy.supported.channels[page] & BIT(channel)))
		return -EINVAL;

	return rdev_set_channel(rdev, page, channel);
}
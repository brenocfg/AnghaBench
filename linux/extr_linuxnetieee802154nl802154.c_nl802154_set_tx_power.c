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
struct genl_info {int /*<<< orphan*/ * attrs; struct cfg802154_registered_device** user_ptr; } ;
struct TYPE_3__ {int tx_powers_size; scalar_t__* tx_powers; } ;
struct TYPE_4__ {int flags; TYPE_1__ supported; } ;
struct cfg802154_registered_device {TYPE_2__ wpan_phy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL802154_ATTR_TX_POWER ; 
 int WPAN_PHY_FLAG_TXPOWER ; 
 scalar_t__ nla_get_s32 (int /*<<< orphan*/ ) ; 
 int rdev_set_tx_power (struct cfg802154_registered_device*,scalar_t__) ; 

__attribute__((used)) static int nl802154_set_tx_power(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg802154_registered_device *rdev = info->user_ptr[0];
	s32 power;
	int i;

	if (!(rdev->wpan_phy.flags & WPAN_PHY_FLAG_TXPOWER))
		return -EOPNOTSUPP;

	if (!info->attrs[NL802154_ATTR_TX_POWER])
		return -EINVAL;

	power = nla_get_s32(info->attrs[NL802154_ATTR_TX_POWER]);

	for (i = 0; i < rdev->wpan_phy.supported.tx_powers_size; i++) {
		if (power == rdev->wpan_phy.supported.tx_powers[i])
			return rdev_set_tx_power(rdev, power);
	}

	return -EINVAL;
}
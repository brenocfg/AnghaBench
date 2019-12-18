#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct genl_info {scalar_t__* attrs; struct cfg802154_registered_device** user_ptr; } ;
struct TYPE_4__ {int iftypes; } ;
struct TYPE_5__ {TYPE_1__ supported; } ;
struct cfg802154_registered_device {TYPE_3__* ops; TYPE_2__ wpan_phy; } ;
typedef  enum nl802154_iftype { ____Placeholder_nl802154_iftype } nl802154_iftype ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_6__ {int /*<<< orphan*/  add_virtual_intf; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NET_NAME_USER ; 
 size_t NL802154_ATTR_EXTENDED_ADDR ; 
 size_t NL802154_ATTR_IFNAME ; 
 size_t NL802154_ATTR_IFTYPE ; 
 int NL802154_IFTYPE_MAX ; 
 int NL802154_IFTYPE_UNSPEC ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  nla_data (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_le64 (scalar_t__) ; 
 int nla_get_u32 (scalar_t__) ; 
 int rdev_add_virtual_intf (struct cfg802154_registered_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl802154_new_interface(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg802154_registered_device *rdev = info->user_ptr[0];
	enum nl802154_iftype type = NL802154_IFTYPE_UNSPEC;
	__le64 extended_addr = cpu_to_le64(0x0000000000000000ULL);

	/* TODO avoid failing a new interface
	 * creation due to pending removal?
	 */

	if (!info->attrs[NL802154_ATTR_IFNAME])
		return -EINVAL;

	if (info->attrs[NL802154_ATTR_IFTYPE]) {
		type = nla_get_u32(info->attrs[NL802154_ATTR_IFTYPE]);
		if (type > NL802154_IFTYPE_MAX ||
		    !(rdev->wpan_phy.supported.iftypes & BIT(type)))
			return -EINVAL;
	}

	if (info->attrs[NL802154_ATTR_EXTENDED_ADDR])
		extended_addr = nla_get_le64(info->attrs[NL802154_ATTR_EXTENDED_ADDR]);

	if (!rdev->ops->add_virtual_intf)
		return -EOPNOTSUPP;

	return rdev_add_virtual_intf(rdev,
				     nla_data(info->attrs[NL802154_ATTR_IFNAME]),
				     NET_NAME_USER, type, extended_addr);
}
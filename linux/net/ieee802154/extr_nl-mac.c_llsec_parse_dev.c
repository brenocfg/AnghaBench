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
struct ieee802154_llsec_device {int seclevel_exempt; scalar_t__ key_mode; int /*<<< orphan*/  frame_counter; int /*<<< orphan*/  hwaddr; void* short_addr; void* pan_id; } ;
struct genl_info {scalar_t__* attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE802154_ADDR_UNDEF ; 
 size_t IEEE802154_ATTR_HW_ADDR ; 
 size_t IEEE802154_ATTR_LLSEC_DEV_KEY_MODE ; 
 size_t IEEE802154_ATTR_LLSEC_DEV_OVERRIDE ; 
 size_t IEEE802154_ATTR_LLSEC_FRAME_COUNTER ; 
 size_t IEEE802154_ATTR_PAN_ID ; 
 size_t IEEE802154_ATTR_SHORT_ADDR ; 
 scalar_t__ __IEEE802154_LLSEC_DEVKEY_MAX ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee802154_llsec_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_get_hwaddr (scalar_t__) ; 
 void* nla_get_shortaddr (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u32 (scalar_t__) ; 
 scalar_t__ nla_get_u8 (scalar_t__) ; 

__attribute__((used)) static int
llsec_parse_dev(struct genl_info *info,
		struct ieee802154_llsec_device *dev)
{
	memset(dev, 0, sizeof(*dev));

	if (!info->attrs[IEEE802154_ATTR_LLSEC_FRAME_COUNTER] ||
	    !info->attrs[IEEE802154_ATTR_HW_ADDR] ||
	    !info->attrs[IEEE802154_ATTR_LLSEC_DEV_OVERRIDE] ||
	    !info->attrs[IEEE802154_ATTR_LLSEC_DEV_KEY_MODE] ||
	    (!!info->attrs[IEEE802154_ATTR_PAN_ID] !=
	     !!info->attrs[IEEE802154_ATTR_SHORT_ADDR]))
		return -EINVAL;

	if (info->attrs[IEEE802154_ATTR_PAN_ID]) {
		dev->pan_id = nla_get_shortaddr(info->attrs[IEEE802154_ATTR_PAN_ID]);
		dev->short_addr = nla_get_shortaddr(info->attrs[IEEE802154_ATTR_SHORT_ADDR]);
	} else {
		dev->short_addr = cpu_to_le16(IEEE802154_ADDR_UNDEF);
	}

	dev->hwaddr = nla_get_hwaddr(info->attrs[IEEE802154_ATTR_HW_ADDR]);
	dev->frame_counter = nla_get_u32(info->attrs[IEEE802154_ATTR_LLSEC_FRAME_COUNTER]);
	dev->seclevel_exempt = !!nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_DEV_OVERRIDE]);
	dev->key_mode = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_DEV_KEY_MODE]);

	if (dev->key_mode >= __IEEE802154_LLSEC_DEVKEY_MAX)
		return -EINVAL;

	return 0;
}
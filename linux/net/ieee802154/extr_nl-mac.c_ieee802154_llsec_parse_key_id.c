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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {void* extended_addr; int /*<<< orphan*/  mode; void* short_addr; void* pan_id; } ;
struct ieee802154_llsec_key_id {int mode; void* extended_source; int /*<<< orphan*/  short_source; void* id; TYPE_1__ device_addr; } ;
struct genl_info {scalar_t__* attrs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IEEE802154_ADDR_LONG ; 
 int /*<<< orphan*/  IEEE802154_ADDR_SHORT ; 
 size_t IEEE802154_ATTR_HW_ADDR ; 
 size_t IEEE802154_ATTR_LLSEC_KEY_ID ; 
 size_t IEEE802154_ATTR_LLSEC_KEY_MODE ; 
 size_t IEEE802154_ATTR_LLSEC_KEY_SOURCE_EXTENDED ; 
 size_t IEEE802154_ATTR_LLSEC_KEY_SOURCE_SHORT ; 
 size_t IEEE802154_ATTR_PAN_ID ; 
 size_t IEEE802154_ATTR_SHORT_ADDR ; 
#define  IEEE802154_SCF_KEY_HW_INDEX 129 
 int IEEE802154_SCF_KEY_IMPLICIT ; 
#define  IEEE802154_SCF_KEY_SHORT_INDEX 128 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee802154_llsec_key_id*,int /*<<< orphan*/ ,int) ; 
 void* nla_get_hwaddr (scalar_t__) ; 
 void* nla_get_shortaddr (scalar_t__) ; 
 int /*<<< orphan*/  nla_get_u32 (scalar_t__) ; 
 void* nla_get_u8 (scalar_t__) ; 

__attribute__((used)) static int
ieee802154_llsec_parse_key_id(struct genl_info *info,
			      struct ieee802154_llsec_key_id *desc)
{
	memset(desc, 0, sizeof(*desc));

	if (!info->attrs[IEEE802154_ATTR_LLSEC_KEY_MODE])
		return -EINVAL;

	desc->mode = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_KEY_MODE]);

	if (desc->mode == IEEE802154_SCF_KEY_IMPLICIT) {
		if (!info->attrs[IEEE802154_ATTR_PAN_ID] &&
		    !(info->attrs[IEEE802154_ATTR_SHORT_ADDR] ||
		      info->attrs[IEEE802154_ATTR_HW_ADDR]))
			return -EINVAL;

		desc->device_addr.pan_id = nla_get_shortaddr(info->attrs[IEEE802154_ATTR_PAN_ID]);

		if (info->attrs[IEEE802154_ATTR_SHORT_ADDR]) {
			desc->device_addr.mode = IEEE802154_ADDR_SHORT;
			desc->device_addr.short_addr = nla_get_shortaddr(info->attrs[IEEE802154_ATTR_SHORT_ADDR]);
		} else {
			desc->device_addr.mode = IEEE802154_ADDR_LONG;
			desc->device_addr.extended_addr = nla_get_hwaddr(info->attrs[IEEE802154_ATTR_HW_ADDR]);
		}
	}

	if (desc->mode != IEEE802154_SCF_KEY_IMPLICIT &&
	    !info->attrs[IEEE802154_ATTR_LLSEC_KEY_ID])
		return -EINVAL;

	if (desc->mode == IEEE802154_SCF_KEY_SHORT_INDEX &&
	    !info->attrs[IEEE802154_ATTR_LLSEC_KEY_SOURCE_SHORT])
		return -EINVAL;

	if (desc->mode == IEEE802154_SCF_KEY_HW_INDEX &&
	    !info->attrs[IEEE802154_ATTR_LLSEC_KEY_SOURCE_EXTENDED])
		return -EINVAL;

	if (desc->mode != IEEE802154_SCF_KEY_IMPLICIT)
		desc->id = nla_get_u8(info->attrs[IEEE802154_ATTR_LLSEC_KEY_ID]);

	switch (desc->mode) {
	case IEEE802154_SCF_KEY_SHORT_INDEX:
	{
		u32 source = nla_get_u32(info->attrs[IEEE802154_ATTR_LLSEC_KEY_SOURCE_SHORT]);

		desc->short_source = cpu_to_le32(source);
		break;
	}
	case IEEE802154_SCF_KEY_HW_INDEX:
		desc->extended_source = nla_get_hwaddr(info->attrs[IEEE802154_ATTR_LLSEC_KEY_SOURCE_EXTENDED]);
		break;
	}

	return 0;
}
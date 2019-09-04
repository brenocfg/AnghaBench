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
struct wpan_phy_cca {scalar_t__ mode; scalar_t__ opt; } ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; struct cfg802154_registered_device** user_ptr; } ;
struct TYPE_3__ {int cca_modes; int cca_opts; } ;
struct TYPE_4__ {int flags; TYPE_1__ supported; } ;
struct cfg802154_registered_device {TYPE_2__ wpan_phy; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 size_t NL802154_ATTR_CCA_MODE ; 
 size_t NL802154_ATTR_CCA_OPT ; 
 scalar_t__ NL802154_CCA_ATTR_MAX ; 
 scalar_t__ NL802154_CCA_ENERGY ; 
 scalar_t__ NL802154_CCA_ENERGY_CARRIER ; 
 scalar_t__ NL802154_CCA_OPT_ATTR_MAX ; 
 int WPAN_PHY_FLAG_CCA_MODE ; 
 void* nla_get_u32 (int /*<<< orphan*/ ) ; 
 int rdev_set_cca_mode (struct cfg802154_registered_device*,struct wpan_phy_cca*) ; 

__attribute__((used)) static int nl802154_set_cca_mode(struct sk_buff *skb, struct genl_info *info)
{
	struct cfg802154_registered_device *rdev = info->user_ptr[0];
	struct wpan_phy_cca cca;

	if (!(rdev->wpan_phy.flags & WPAN_PHY_FLAG_CCA_MODE))
		return -EOPNOTSUPP;

	if (!info->attrs[NL802154_ATTR_CCA_MODE])
		return -EINVAL;

	cca.mode = nla_get_u32(info->attrs[NL802154_ATTR_CCA_MODE]);
	/* checking 802.15.4 constraints */
	if (cca.mode < NL802154_CCA_ENERGY ||
	    cca.mode > NL802154_CCA_ATTR_MAX ||
	    !(rdev->wpan_phy.supported.cca_modes & BIT(cca.mode)))
		return -EINVAL;

	if (cca.mode == NL802154_CCA_ENERGY_CARRIER) {
		if (!info->attrs[NL802154_ATTR_CCA_OPT])
			return -EINVAL;

		cca.opt = nla_get_u32(info->attrs[NL802154_ATTR_CCA_OPT]);
		if (cca.opt > NL802154_CCA_OPT_ATTR_MAX ||
		    !(rdev->wpan_phy.supported.cca_opts & BIT(cca.opt)))
			return -EINVAL;
	}

	return rdev_set_cca_mode(rdev, &cca);
}
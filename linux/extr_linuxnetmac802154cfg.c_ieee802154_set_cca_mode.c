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
struct wpan_phy_cca {int dummy; } ;
struct wpan_phy {struct wpan_phy_cca cca; } ;
struct ieee802154_local {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int drv_set_cca_mode (struct ieee802154_local*,struct wpan_phy_cca const*) ; 
 scalar_t__ wpan_phy_cca_cmp (struct wpan_phy_cca*,struct wpan_phy_cca const*) ; 
 struct ieee802154_local* wpan_phy_priv (struct wpan_phy*) ; 

__attribute__((used)) static int
ieee802154_set_cca_mode(struct wpan_phy *wpan_phy,
			const struct wpan_phy_cca *cca)
{
	struct ieee802154_local *local = wpan_phy_priv(wpan_phy);
	int ret;

	ASSERT_RTNL();

	if (wpan_phy_cca_cmp(&wpan_phy->cca, cca))
		return 0;

	ret = drv_set_cca_mode(local, cca);
	if (!ret)
		wpan_phy->cca = *cca;

	return ret;
}
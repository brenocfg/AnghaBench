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
struct wpan_phy {int /*<<< orphan*/  cca_ed_level; } ;
struct ieee802154_local {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int drv_set_cca_ed_level (struct ieee802154_local*,int /*<<< orphan*/ ) ; 
 struct ieee802154_local* wpan_phy_priv (struct wpan_phy*) ; 

__attribute__((used)) static int
ieee802154_set_cca_ed_level(struct wpan_phy *wpan_phy, s32 ed_level)
{
	struct ieee802154_local *local = wpan_phy_priv(wpan_phy);
	int ret;

	ASSERT_RTNL();

	if (wpan_phy->cca_ed_level == ed_level)
		return 0;

	ret = drv_set_cca_ed_level(local, ed_level);
	if (!ret)
		wpan_phy->cca_ed_level = ed_level;

	return ret;
}
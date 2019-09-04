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
typedef  int /*<<< orphan*/  u32 ;
struct phylink_link_state {int /*<<< orphan*/  advertising; int /*<<< orphan*/  interface; } ;
struct TYPE_6__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  interface; } ;
struct phylink {int /*<<< orphan*/  supported; int /*<<< orphan*/  netdev; int /*<<< orphan*/  state_mutex; TYPE_3__ link_config; struct phy_device* phydev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct phy_device {scalar_t__ irq; int /*<<< orphan*/  advertising; int /*<<< orphan*/  lock; TYPE_2__* drv; TYPE_1__ mdio; int /*<<< orphan*/  phy_link_change; struct phylink* phylink; int /*<<< orphan*/  supported; } ;
typedef  int /*<<< orphan*/  config ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  Asym_Pause ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  __ETHTOOL_DECLARE_LINK_MODE_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct phylink_link_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start_interrupts (struct phy_device*) ; 
 int /*<<< orphan*/  phy_start_machine (struct phy_device*) ; 
 int /*<<< orphan*/  phylink_phy_change ; 
 int /*<<< orphan*/  phylink_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ phylink_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phylink_validate (struct phylink*,int /*<<< orphan*/ ,struct phylink_link_state*) ; 
 int /*<<< orphan*/  supported ; 

__attribute__((used)) static int phylink_bringup_phy(struct phylink *pl, struct phy_device *phy)
{
	struct phylink_link_state config;
	__ETHTOOL_DECLARE_LINK_MODE_MASK(supported);
	u32 advertising;
	int ret;

	memset(&config, 0, sizeof(config));
	ethtool_convert_legacy_u32_to_link_mode(supported, phy->supported);
	ethtool_convert_legacy_u32_to_link_mode(config.advertising,
						phy->advertising);
	config.interface = pl->link_config.interface;

	/*
	 * This is the new way of dealing with flow control for PHYs,
	 * as described by Timur Tabi in commit 529ed1275263 ("net: phy:
	 * phy drivers should not set SUPPORTED_[Asym_]Pause") except
	 * using our validate call to the MAC, we rely upon the MAC
	 * clearing the bits from both supported and advertising fields.
	 */
	if (phylink_test(supported, Pause))
		phylink_set(config.advertising, Pause);
	if (phylink_test(supported, Asym_Pause))
		phylink_set(config.advertising, Asym_Pause);

	ret = phylink_validate(pl, supported, &config);
	if (ret)
		return ret;

	phy->phylink = pl;
	phy->phy_link_change = phylink_phy_change;

	netdev_info(pl->netdev,
		    "PHY [%s] driver [%s]\n", dev_name(&phy->mdio.dev),
		    phy->drv->name);

	mutex_lock(&phy->lock);
	mutex_lock(&pl->state_mutex);
	pl->phydev = phy;
	linkmode_copy(pl->supported, supported);
	linkmode_copy(pl->link_config.advertising, config.advertising);

	/* Restrict the phy advertisement according to the MAC support. */
	ethtool_convert_link_mode_to_legacy_u32(&advertising, config.advertising);
	phy->advertising = advertising;
	mutex_unlock(&pl->state_mutex);
	mutex_unlock(&phy->lock);

	netdev_dbg(pl->netdev,
		   "phy: setting supported %*pb advertising 0x%08x\n",
		   __ETHTOOL_LINK_MODE_MASK_NBITS, pl->supported,
		   phy->advertising);

	phy_start_machine(phy);
	if (phy->irq > 0)
		phy_start_interrupts(phy);

	return 0;
}
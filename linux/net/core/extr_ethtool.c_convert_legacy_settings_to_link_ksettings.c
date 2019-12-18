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
struct TYPE_4__ {int /*<<< orphan*/  eth_tp_mdix_ctrl; int /*<<< orphan*/  eth_tp_mdix; int /*<<< orphan*/  mdio_support; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;
struct ethtool_cmd {int /*<<< orphan*/  eth_tp_mdix_ctrl; int /*<<< orphan*/  eth_tp_mdix; int /*<<< orphan*/  mdio_support; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; scalar_t__ maxrxpkt; scalar_t__ maxtxpkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ethtool_cmd_speed (struct ethtool_cmd const*) ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
convert_legacy_settings_to_link_ksettings(
	struct ethtool_link_ksettings *link_ksettings,
	const struct ethtool_cmd *legacy_settings)
{
	bool retval = true;

	memset(link_ksettings, 0, sizeof(*link_ksettings));

	/* This is used to tell users that driver is still using these
	 * deprecated legacy fields, and they should not use
	 * %ETHTOOL_GLINKSETTINGS/%ETHTOOL_SLINKSETTINGS
	 */
	if (legacy_settings->maxtxpkt ||
	    legacy_settings->maxrxpkt)
		retval = false;

	ethtool_convert_legacy_u32_to_link_mode(
		link_ksettings->link_modes.supported,
		legacy_settings->supported);
	ethtool_convert_legacy_u32_to_link_mode(
		link_ksettings->link_modes.advertising,
		legacy_settings->advertising);
	ethtool_convert_legacy_u32_to_link_mode(
		link_ksettings->link_modes.lp_advertising,
		legacy_settings->lp_advertising);
	link_ksettings->base.speed
		= ethtool_cmd_speed(legacy_settings);
	link_ksettings->base.duplex
		= legacy_settings->duplex;
	link_ksettings->base.port
		= legacy_settings->port;
	link_ksettings->base.phy_address
		= legacy_settings->phy_address;
	link_ksettings->base.autoneg
		= legacy_settings->autoneg;
	link_ksettings->base.mdio_support
		= legacy_settings->mdio_support;
	link_ksettings->base.eth_tp_mdix
		= legacy_settings->eth_tp_mdix;
	link_ksettings->base.eth_tp_mdix_ctrl
		= legacy_settings->eth_tp_mdix_ctrl;
	return retval;
}
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
struct TYPE_4__ {int /*<<< orphan*/  transceiver; int /*<<< orphan*/  eth_tp_mdix_ctrl; int /*<<< orphan*/  eth_tp_mdix; int /*<<< orphan*/  mdio_support; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;
struct ethtool_cmd {int /*<<< orphan*/  transceiver; int /*<<< orphan*/  eth_tp_mdix_ctrl; int /*<<< orphan*/  eth_tp_mdix; int /*<<< orphan*/  mdio_support; int /*<<< orphan*/  autoneg; int /*<<< orphan*/  phy_address; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int /*<<< orphan*/ ) ; 
 int ethtool_convert_link_mode_to_legacy_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ethtool_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
convert_link_ksettings_to_legacy_settings(
	struct ethtool_cmd *legacy_settings,
	const struct ethtool_link_ksettings *link_ksettings)
{
	bool retval = true;

	memset(legacy_settings, 0, sizeof(*legacy_settings));
	/* this also clears the deprecated fields in legacy structure:
	 * __u8		transceiver;
	 * __u32	maxtxpkt;
	 * __u32	maxrxpkt;
	 */

	retval &= ethtool_convert_link_mode_to_legacy_u32(
		&legacy_settings->supported,
		link_ksettings->link_modes.supported);
	retval &= ethtool_convert_link_mode_to_legacy_u32(
		&legacy_settings->advertising,
		link_ksettings->link_modes.advertising);
	retval &= ethtool_convert_link_mode_to_legacy_u32(
		&legacy_settings->lp_advertising,
		link_ksettings->link_modes.lp_advertising);
	ethtool_cmd_speed_set(legacy_settings, link_ksettings->base.speed);
	legacy_settings->duplex
		= link_ksettings->base.duplex;
	legacy_settings->port
		= link_ksettings->base.port;
	legacy_settings->phy_address
		= link_ksettings->base.phy_address;
	legacy_settings->autoneg
		= link_ksettings->base.autoneg;
	legacy_settings->mdio_support
		= link_ksettings->base.mdio_support;
	legacy_settings->eth_tp_mdix
		= link_ksettings->base.eth_tp_mdix;
	legacy_settings->eth_tp_mdix_ctrl
		= link_ksettings->base.eth_tp_mdix_ctrl;
	legacy_settings->transceiver
		= link_ksettings->base.transceiver;
	return retval;
}
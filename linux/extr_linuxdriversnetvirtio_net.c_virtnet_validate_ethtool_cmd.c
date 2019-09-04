#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lp_advertising; int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_5__ {scalar_t__ link_mode_masks_nwords; scalar_t__ cmd; scalar_t__ duplex; int /*<<< orphan*/  port; scalar_t__ speed; } ;
struct ethtool_link_ksettings {TYPE_1__ link_modes; TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_OTHER ; 
 int /*<<< orphan*/  __ETHTOOL_LINK_MODE_MASK_NBITS ; 
 int /*<<< orphan*/  advertising ; 
 scalar_t__ bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_link_ksettings_zero_link_mode (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static bool
virtnet_validate_ethtool_cmd(const struct ethtool_link_ksettings *cmd)
{
	struct ethtool_link_ksettings diff1 = *cmd;
	struct ethtool_link_ksettings diff2 = {};

	/* cmd is always set so we need to clear it, validate the port type
	 * and also without autonegotiation we can ignore advertising
	 */
	diff1.base.speed = 0;
	diff2.base.port = PORT_OTHER;
	ethtool_link_ksettings_zero_link_mode(&diff1, advertising);
	diff1.base.duplex = 0;
	diff1.base.cmd = 0;
	diff1.base.link_mode_masks_nwords = 0;

	return !memcmp(&diff1.base, &diff2.base, sizeof(diff1.base)) &&
		bitmap_empty(diff1.link_modes.supported,
			     __ETHTOOL_LINK_MODE_MASK_NBITS) &&
		bitmap_empty(diff1.link_modes.advertising,
			     __ETHTOOL_LINK_MODE_MASK_NBITS) &&
		bitmap_empty(diff1.link_modes.lp_advertising,
			     __ETHTOOL_LINK_MODE_MASK_NBITS);
}
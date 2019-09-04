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
struct TYPE_2__ {int /*<<< orphan*/  autoneg; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ef4_mdio_set_link_ksettings (struct ef4_nic*,struct ethtool_link_ksettings const*) ; 

__attribute__((used)) static int
tenxpress_set_link_ksettings(struct ef4_nic *efx,
			     const struct ethtool_link_ksettings *cmd)
{
	if (!cmd->base.autoneg)
		return -EINVAL;

	return ef4_mdio_set_link_ksettings(efx, cmd);
}
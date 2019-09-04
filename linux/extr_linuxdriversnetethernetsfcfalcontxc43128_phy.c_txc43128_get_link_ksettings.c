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
struct ethtool_link_ksettings {int dummy; } ;
struct ef4_nic {int /*<<< orphan*/  mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdio45_ethtool_ksettings_get (int /*<<< orphan*/ *,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static void txc43128_get_link_ksettings(struct ef4_nic *efx,
					struct ethtool_link_ksettings *cmd)
{
	mdio45_ethtool_ksettings_get(&efx->mdio, cmd);
}
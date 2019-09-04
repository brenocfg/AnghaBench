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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; } ;
struct TYPE_3__ {int speed; scalar_t__ autoneg; scalar_t__ duplex; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;
struct efx_nic {int /*<<< orphan*/  loopback_mode; int /*<<< orphan*/  fec_config; struct efx_mcdi_phy_data* phy_data; } ;
struct efx_mcdi_phy_data {int forced_cap; } ;

/* Variables and functions */
 int EINVAL ; 
 int MC_CMD_PHY_CAP_100000FDX_LBN ; 
 int MC_CMD_PHY_CAP_10000FDX_LBN ; 
 int MC_CMD_PHY_CAP_1000FDX_LBN ; 
 int MC_CMD_PHY_CAP_1000HDX_LBN ; 
 int MC_CMD_PHY_CAP_100FDX_LBN ; 
 int MC_CMD_PHY_CAP_100HDX_LBN ; 
 int MC_CMD_PHY_CAP_10FDX_LBN ; 
 int MC_CMD_PHY_CAP_10HDX_LBN ; 
 int MC_CMD_PHY_CAP_25000FDX_LBN ; 
 int MC_CMD_PHY_CAP_40000FDX_LBN ; 
 int MC_CMD_PHY_CAP_50000FDX_LBN ; 
 int MC_CMD_PHY_CAP_AN_LBN ; 
 int /*<<< orphan*/  efx_get_mcdi_phy_flags (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_link_clear_advertising (struct efx_nic*) ; 
 int /*<<< orphan*/  efx_link_set_advertising (struct efx_nic*,int /*<<< orphan*/ ) ; 
 int efx_mcdi_set_link (struct efx_nic*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ethtool_fec_caps_to_mcdi (int /*<<< orphan*/ ) ; 
 int ethtool_linkset_to_mcdi_cap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
efx_mcdi_phy_set_link_ksettings(struct efx_nic *efx,
				const struct ethtool_link_ksettings *cmd)
{
	struct efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	u32 caps;
	int rc;

	if (cmd->base.autoneg) {
		caps = (ethtool_linkset_to_mcdi_cap(cmd->link_modes.advertising) |
			1 << MC_CMD_PHY_CAP_AN_LBN);
	} else if (cmd->base.duplex) {
		switch (cmd->base.speed) {
		case 10:     caps = 1 << MC_CMD_PHY_CAP_10FDX_LBN;     break;
		case 100:    caps = 1 << MC_CMD_PHY_CAP_100FDX_LBN;    break;
		case 1000:   caps = 1 << MC_CMD_PHY_CAP_1000FDX_LBN;   break;
		case 10000:  caps = 1 << MC_CMD_PHY_CAP_10000FDX_LBN;  break;
		case 40000:  caps = 1 << MC_CMD_PHY_CAP_40000FDX_LBN;  break;
		case 100000: caps = 1 << MC_CMD_PHY_CAP_100000FDX_LBN; break;
		case 25000:  caps = 1 << MC_CMD_PHY_CAP_25000FDX_LBN;  break;
		case 50000:  caps = 1 << MC_CMD_PHY_CAP_50000FDX_LBN;  break;
		default:     return -EINVAL;
		}
	} else {
		switch (cmd->base.speed) {
		case 10:     caps = 1 << MC_CMD_PHY_CAP_10HDX_LBN;     break;
		case 100:    caps = 1 << MC_CMD_PHY_CAP_100HDX_LBN;    break;
		case 1000:   caps = 1 << MC_CMD_PHY_CAP_1000HDX_LBN;   break;
		default:     return -EINVAL;
		}
	}

	caps |= ethtool_fec_caps_to_mcdi(efx->fec_config);

	rc = efx_mcdi_set_link(efx, caps, efx_get_mcdi_phy_flags(efx),
			       efx->loopback_mode, 0);
	if (rc)
		return rc;

	if (cmd->base.autoneg) {
		efx_link_set_advertising(efx, cmd->link_modes.advertising);
		phy_cfg->forced_cap = 0;
	} else {
		efx_link_clear_advertising(efx);
		phy_cfg->forced_cap = caps;
	}
	return 0;
}
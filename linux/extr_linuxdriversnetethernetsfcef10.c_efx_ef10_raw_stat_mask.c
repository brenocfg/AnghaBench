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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct efx_nic {TYPE_1__* mcdi; struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {int datapath_caps2; int datapath_caps; } ;
struct TYPE_2__ {int fn_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  HUNT_10G_ONLY_STAT_MASK ; 
 int /*<<< orphan*/  HUNT_40G_EXTRA_STAT_MASK ; 
 int /*<<< orphan*/  HUNT_COMMON_STAT_MASK ; 
 int /*<<< orphan*/  HUNT_PM_AND_RXDP_STAT_MASK ; 
 int MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_LINKCTRL ; 
 int MC_CMD_GET_CAPABILITIES_OUT_PM_AND_RXDP_COUNTERS_LBN ; 
 int MC_CMD_GET_CAPABILITIES_V2_OUT_MAC_STATS_40G_TX_SIZE_BINS_LBN ; 
 int MC_CMD_PHY_CAP_40000FDX_LBN ; 
 int efx_mcdi_phy_get_caps (struct efx_nic*) ; 

__attribute__((used)) static u64 efx_ef10_raw_stat_mask(struct efx_nic *efx)
{
	u64 raw_mask = HUNT_COMMON_STAT_MASK;
	u32 port_caps = efx_mcdi_phy_get_caps(efx);
	struct efx_ef10_nic_data *nic_data = efx->nic_data;

	if (!(efx->mcdi->fn_flags &
	      1 << MC_CMD_DRV_ATTACH_EXT_OUT_FLAG_LINKCTRL))
		return 0;

	if (port_caps & (1 << MC_CMD_PHY_CAP_40000FDX_LBN)) {
		raw_mask |= HUNT_40G_EXTRA_STAT_MASK;
		/* 8000 series have everything even at 40G */
		if (nic_data->datapath_caps2 &
		    (1 << MC_CMD_GET_CAPABILITIES_V2_OUT_MAC_STATS_40G_TX_SIZE_BINS_LBN))
			raw_mask |= HUNT_10G_ONLY_STAT_MASK;
	} else {
		raw_mask |= HUNT_10G_ONLY_STAT_MASK;
	}

	if (nic_data->datapath_caps &
	    (1 << MC_CMD_GET_CAPABILITIES_OUT_PM_AND_RXDP_COUNTERS_LBN))
		raw_mask |= HUNT_PM_AND_RXDP_STAT_MASK;

	return raw_mask;
}
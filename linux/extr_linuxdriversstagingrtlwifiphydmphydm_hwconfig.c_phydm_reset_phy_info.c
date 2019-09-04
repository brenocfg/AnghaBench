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
struct phy_dm_struct {int dummy; } ;
struct dm_phy_status_info {int rx_power; int recv_signal_power; int /*<<< orphan*/  cfo_tail; int /*<<< orphan*/  cfo_short; int /*<<< orphan*/  rx_mimo_evm_dbm; int /*<<< orphan*/  rx_pwr; scalar_t__ rxsc; scalar_t__ is_beamformed; scalar_t__ is_mu_packet; scalar_t__ channel; scalar_t__ bt_coex_pwr_adjust; scalar_t__ signal_strength; scalar_t__ bt_rx_rssi_percentage; int /*<<< orphan*/  rx_snr; int /*<<< orphan*/  rx_mimo_signal_strength; int /*<<< orphan*/  rx_mimo_signal_quality; scalar_t__ rx_count; scalar_t__ band_width; scalar_t__ signal_quality; scalar_t__ rx_pwdb_all; } ;

/* Variables and functions */
 int /*<<< orphan*/  odm_memory_set (struct phy_dm_struct*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void phydm_reset_phy_info(struct phy_dm_struct *phydm,
				 struct dm_phy_status_info *phy_info)
{
	phy_info->rx_pwdb_all = 0;
	phy_info->signal_quality = 0;
	phy_info->band_width = 0;
	phy_info->rx_count = 0;
	odm_memory_set(phydm, phy_info->rx_mimo_signal_quality, 0, 4);
	odm_memory_set(phydm, phy_info->rx_mimo_signal_strength, 0, 4);
	odm_memory_set(phydm, phy_info->rx_snr, 0, 4);

	phy_info->rx_power = -110;
	phy_info->recv_signal_power = -110;
	phy_info->bt_rx_rssi_percentage = 0;
	phy_info->signal_strength = 0;
	phy_info->bt_coex_pwr_adjust = 0;
	phy_info->channel = 0;
	phy_info->is_mu_packet = 0;
	phy_info->is_beamformed = 0;
	phy_info->rxsc = 0;
	odm_memory_set(phydm, phy_info->rx_pwr, -110, 4);
	odm_memory_set(phydm, phy_info->rx_mimo_evm_dbm, 0, 4);
	odm_memory_set(phydm, phy_info->cfo_short, 0, 8);
	odm_memory_set(phydm, phy_info->cfo_tail, 0, 8);
}
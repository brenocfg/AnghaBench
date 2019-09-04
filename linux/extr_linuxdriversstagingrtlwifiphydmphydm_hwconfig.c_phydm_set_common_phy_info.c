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
typedef  void* u8 ;
struct dm_phy_status_info {int is_beamformed; int is_mu_packet; void* band_width; void* signal_quality; int /*<<< orphan*/  rx_pwdb_all; void* rxsc; void* channel; void* recv_signal_power; void* rx_power; } ;
typedef  void* s8 ;

/* Variables and functions */
 int /*<<< orphan*/  odm_query_rx_pwr_percentage (void*) ; 

__attribute__((used)) static void phydm_set_common_phy_info(s8 rx_power, u8 channel,
				      bool is_beamformed, bool is_mu_packet,
				      u8 bandwidth, u8 signal_quality, u8 rxsc,
				      struct dm_phy_status_info *phy_info)
{
	phy_info->rx_power = rx_power; /* RSSI in dB */
	phy_info->recv_signal_power = rx_power; /* RSSI in dB */
	phy_info->channel = channel; /* channel number */
	phy_info->is_beamformed = is_beamformed; /* apply BF */
	phy_info->is_mu_packet = is_mu_packet; /* MU packet */
	phy_info->rxsc = rxsc;
	phy_info->rx_pwdb_all =
		odm_query_rx_pwr_percentage(rx_power); /* RSSI in percentage */
	phy_info->signal_quality = signal_quality; /* signal quality */
	phy_info->band_width = bandwidth; /* bandwidth */
}
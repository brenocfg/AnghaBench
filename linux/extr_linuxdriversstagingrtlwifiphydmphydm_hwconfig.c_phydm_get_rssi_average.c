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
typedef  int u8 ;
typedef  int u32 ;
struct phy_dm_struct {scalar_t__ rssi_a; scalar_t__ rssi_b; } ;
struct dm_phy_status_info {scalar_t__* rx_mimo_signal_strength; } ;

/* Variables and functions */
 size_t ODM_RF_PATH_A ; 
 size_t ODM_RF_PATH_B ; 

__attribute__((used)) static inline u32 phydm_get_rssi_average(struct phy_dm_struct *dm,
					 struct dm_phy_status_info *phy_info)
{
	u8 rssi_max = 0, rssi_min = 0;

	dm->rssi_a = phy_info->rx_mimo_signal_strength[ODM_RF_PATH_A];
	dm->rssi_b = phy_info->rx_mimo_signal_strength[ODM_RF_PATH_B];

	if (phy_info->rx_mimo_signal_strength[ODM_RF_PATH_A] >
	    phy_info->rx_mimo_signal_strength[ODM_RF_PATH_B]) {
		rssi_max = phy_info->rx_mimo_signal_strength[ODM_RF_PATH_A];
		rssi_min = phy_info->rx_mimo_signal_strength[ODM_RF_PATH_B];
	} else {
		rssi_max = phy_info->rx_mimo_signal_strength[ODM_RF_PATH_B];
		rssi_min = phy_info->rx_mimo_signal_strength[ODM_RF_PATH_A];
	}
	if ((rssi_max - rssi_min) < 3)
		return rssi_max;
	else if ((rssi_max - rssi_min) < 6)
		return rssi_max - 1;
	else if ((rssi_max - rssi_min) < 10)
		return rssi_max - 2;
	else
		return rssi_max - 3;
}
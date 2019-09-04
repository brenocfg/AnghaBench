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
struct phy_dm_struct {int dummy; } ;
struct dm_phy_status_info {int signal_strength; int /*<<< orphan*/  rx_pwdb_all; } ;
struct dm_per_pkt_info {int dummy; } ;

/* Variables and functions */
 scalar_t__ odm_signal_scale_mapping (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_get_rx_phy_status_type0 (struct phy_dm_struct*,int*,struct dm_per_pkt_info*,struct dm_phy_status_info*) ; 
 int /*<<< orphan*/  phydm_get_rx_phy_status_type1 (struct phy_dm_struct*,int*,struct dm_per_pkt_info*,struct dm_phy_status_info*) ; 
 int /*<<< orphan*/  phydm_get_rx_phy_status_type2 (struct phy_dm_struct*,int*,struct dm_per_pkt_info*,struct dm_phy_status_info*) ; 
 int /*<<< orphan*/  phydm_process_rssi_for_dm_new_type (struct phy_dm_struct*,struct dm_phy_status_info*,struct dm_per_pkt_info*) ; 
 int /*<<< orphan*/  phydm_reset_phy_info (struct phy_dm_struct*,struct dm_phy_status_info*) ; 

void phydm_rx_phy_status_new_type(struct phy_dm_struct *phydm, u8 *phy_status,
				  struct dm_per_pkt_info *pktinfo,
				  struct dm_phy_status_info *phy_info)
{
	u8 phy_status_type = (*phy_status & 0xf);

	/* Memory reset */
	phydm_reset_phy_info(phydm, phy_info);

	/* Phy status parsing */
	switch (phy_status_type) {
	case 0: {
		phydm_get_rx_phy_status_type0(phydm, phy_status, pktinfo,
					      phy_info);
		break;
	}
	case 1: {
		phydm_get_rx_phy_status_type1(phydm, phy_status, pktinfo,
					      phy_info);
		break;
	}
	case 2: {
		phydm_get_rx_phy_status_type2(phydm, phy_status, pktinfo,
					      phy_info);
		break;
	}
	default:
		return;
	}

	/* Update signal strength to UI, and phy_info->rx_pwdb_all is the
	 * maximum RSSI of all path
	 */
	phy_info->signal_strength =
		(u8)(odm_signal_scale_mapping(phydm, phy_info->rx_pwdb_all));

	/* Calculate average RSSI and smoothed RSSI */
	phydm_process_rssi_for_dm_new_type(phydm, phy_info, pktinfo);
}
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
typedef  int /*<<< orphan*/  u8 ;
struct phy_dm_struct {int support_ic_type; } ;
struct dm_phy_status_info {int dummy; } ;
struct dm_per_pkt_info {int dummy; } ;

/* Variables and functions */
 int ODM_IC_11AC_SERIES ; 
 int ODM_IC_11N_SERIES ; 
 int ODM_IC_PHY_STATUE_NEW_TYPE ; 
 int /*<<< orphan*/  odm_phy_status_query_92c_series (struct phy_dm_struct*,struct dm_phy_status_info*,int /*<<< orphan*/ *,struct dm_per_pkt_info*) ; 
 int /*<<< orphan*/  odm_phy_status_query_jaguar_series (struct phy_dm_struct*,struct dm_phy_status_info*,int /*<<< orphan*/ *,struct dm_per_pkt_info*) ; 
 int /*<<< orphan*/  phydm_rx_phy_status_new_type (struct phy_dm_struct*,int /*<<< orphan*/ *,struct dm_per_pkt_info*,struct dm_phy_status_info*) ; 

void odm_phy_status_query(struct phy_dm_struct *dm,
			  struct dm_phy_status_info *phy_info, u8 *phy_status,
			  struct dm_per_pkt_info *pktinfo)
{
	if (dm->support_ic_type & ODM_IC_PHY_STATUE_NEW_TYPE) {
		phydm_rx_phy_status_new_type(dm, phy_status, pktinfo, phy_info);
		return;
	}

	if (dm->support_ic_type & ODM_IC_11AC_SERIES)
		odm_phy_status_query_jaguar_series(dm, phy_info, phy_status,
						   pktinfo);

	if (dm->support_ic_type & ODM_IC_11N_SERIES)
		odm_phy_status_query_92c_series(dm, phy_info, phy_status,
						pktinfo);
}
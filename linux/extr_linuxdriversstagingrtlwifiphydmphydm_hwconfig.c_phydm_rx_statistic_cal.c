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
typedef  int u8 ;
struct phy_status_rpt_jaguar2_type1 {int gid; } ;
struct TYPE_2__ {int* num_of_ppdu; int* gid_num; int /*<<< orphan*/ * num_qry_vht_pkt; int /*<<< orphan*/ * num_qry_mu_vht_pkt; } ;
struct phy_dm_struct {TYPE_1__ phy_dbg_info; } ;
struct dm_per_pkt_info {int data_rate; size_t ppdu_cnt; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ODM_RATEVHTSS1MCS0 ; 

__attribute__((used)) static void phydm_rx_statistic_cal(struct phy_dm_struct *phydm, u8 *phy_status,
				   struct dm_per_pkt_info *pktinfo)
{
	struct phy_status_rpt_jaguar2_type1 *phy_sta_rpt =
		(struct phy_status_rpt_jaguar2_type1 *)phy_status;
	u8 date_rate = pktinfo->data_rate & ~(BIT(7));

	if ((phy_sta_rpt->gid != 0) && (phy_sta_rpt->gid != 63)) {
		if (date_rate >= ODM_RATEVHTSS1MCS0) {
			phydm->phy_dbg_info
				.num_qry_mu_vht_pkt[date_rate - 0x2C]++;
			phydm->phy_dbg_info.num_of_ppdu[pktinfo->ppdu_cnt] =
				date_rate | BIT(7);
			phydm->phy_dbg_info.gid_num[pktinfo->ppdu_cnt] =
				phy_sta_rpt->gid;
		}

	} else {
		if (date_rate >= ODM_RATEVHTSS1MCS0) {
			phydm->phy_dbg_info.num_qry_vht_pkt[date_rate - 0x2C]++;
			phydm->phy_dbg_info.num_of_ppdu[pktinfo->ppdu_cnt] =
				date_rate;
			phydm->phy_dbg_info.gid_num[pktinfo->ppdu_cnt] =
				phy_sta_rpt->gid;
		}
	}
}
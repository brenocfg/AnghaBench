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
typedef  scalar_t__ u8 ;
struct phy_dm_struct {int support_ability; scalar_t__ num_rf_path; } ;
struct dm_per_pkt_info {scalar_t__ is_packet_match_bssid; } ;
struct cfo_tracking {int packet_count; int /*<<< orphan*/ * CFO_cnt; int /*<<< orphan*/ * CFO_tail; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int ODM_BB_CFO_TRACKING ; 
 int /*<<< orphan*/  PHYDM_CFOTRACK ; 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 

void odm_parsing_cfo(void *dm_void, void *pktinfo_void, s8 *pcfotail, u8 num_ss)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct dm_per_pkt_info *pktinfo =
		(struct dm_per_pkt_info *)pktinfo_void;
	struct cfo_tracking *cfo_track =
		(struct cfo_tracking *)phydm_get_structure(dm, PHYDM_CFOTRACK);
	u8 i;

	if (!(dm->support_ability & ODM_BB_CFO_TRACKING))
		return;

	if (pktinfo->is_packet_match_bssid) {
		if (num_ss > dm->num_rf_path) /*For fool proof*/
			num_ss = dm->num_rf_path;

		/* 3 Update CFO report for path-A & path-B */
		/* Only paht-A and path-B have CFO tail and short CFO */
		for (i = 0; i < num_ss; i++) {
			cfo_track->CFO_tail[i] += pcfotail[i];
			cfo_track->CFO_cnt[i]++;
		}

		/* 3 Update packet counter */
		if (cfo_track->packet_count == 0xffffffff)
			cfo_track->packet_count = 0;
		else
			cfo_track->packet_count++;
	}
}
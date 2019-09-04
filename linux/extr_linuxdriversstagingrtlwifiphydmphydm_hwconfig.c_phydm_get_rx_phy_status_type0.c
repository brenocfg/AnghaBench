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
typedef  int u8 ;
struct phy_status_rpt_jaguar2_type0 {int signal_quality; int lna_h; int lna_l; int vga; int /*<<< orphan*/  antidx_d; int /*<<< orphan*/  antidx_c; int /*<<< orphan*/  antidx_b; int /*<<< orphan*/  antidx_a; int /*<<< orphan*/  rxsc; int /*<<< orphan*/  channel; scalar_t__ pwdb; } ;
struct TYPE_4__ {int /*<<< orphan*/  antsel_rx_keep_3; int /*<<< orphan*/  antsel_rx_keep_2; int /*<<< orphan*/  antsel_rx_keep_1; int /*<<< orphan*/  antsel_rx_keep_0; } ;
struct TYPE_3__ {int is_ldpc_pkt; int is_stbc_pkt; int /*<<< orphan*/  num_qry_phy_status_cck; } ;
struct phy_dm_struct {TYPE_2__ dm_fat_table; TYPE_1__ phy_dbg_info; int /*<<< orphan*/  cck_new_agc; } ;
struct dm_phy_status_info {int dummy; } ;
struct dm_per_pkt_info {scalar_t__ is_packet_match_bssid; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_BW20M ; 
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  phydm_set_common_phy_info (scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct dm_phy_status_info*) ; 
 int /*<<< orphan*/  phydm_set_per_path_phy_info (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_phy_status_info*) ; 

__attribute__((used)) static void phydm_get_rx_phy_status_type0(struct phy_dm_struct *dm,
					  u8 *phy_status,
					  struct dm_per_pkt_info *pktinfo,
					  struct dm_phy_status_info *phy_info)
{
	/* type 0 is used for cck packet */

	struct phy_status_rpt_jaguar2_type0 *phy_sta_rpt =
		(struct phy_status_rpt_jaguar2_type0 *)phy_status;
	u8 sq = 0;
	s8 rx_power = phy_sta_rpt->pwdb - 110;

	/* JJ ADD 20161014 */

	/* Calculate Signal Quality*/
	if (pktinfo->is_packet_match_bssid) {
		if (phy_sta_rpt->signal_quality >= 64) {
			sq = 0;
		} else if (phy_sta_rpt->signal_quality <= 20) {
			sq = 100;
		} else {
			/* mapping to 2~99% */
			sq = 64 - phy_sta_rpt->signal_quality;
			sq = ((sq << 3) + sq) >> 2;
		}
	}

	/* Modify CCK PWDB if old AGC */
	if (!dm->cck_new_agc) {
		u8 lna_idx, vga_idx;

		lna_idx = ((phy_sta_rpt->lna_h << 3) | phy_sta_rpt->lna_l);
		vga_idx = phy_sta_rpt->vga;

		/* JJ ADD 20161014 */

		/* Need to do !! */
		/*if (dm->support_ic_type & ODM_RTL8822B) */
		/*rx_power = odm_CCKRSSI_8822B(LNA_idx, VGA_idx);*/
	}

	/* Update CCK packet counter */
	dm->phy_dbg_info.num_qry_phy_status_cck++;

	/*CCK no STBC and LDPC*/
	dm->phy_dbg_info.is_ldpc_pkt = false;
	dm->phy_dbg_info.is_stbc_pkt = false;

	/* Update Common information */
	phydm_set_common_phy_info(rx_power, phy_sta_rpt->channel, false, false,
				  ODM_BW20M, sq, phy_sta_rpt->rxsc, phy_info);

	/* Update CCK pwdb */
	/* Update per-path information */
	phydm_set_per_path_phy_info(ODM_RF_PATH_A, rx_power, 0, 0, 0, phy_info);

	dm->dm_fat_table.antsel_rx_keep_0 = phy_sta_rpt->antidx_a;
	dm->dm_fat_table.antsel_rx_keep_1 = phy_sta_rpt->antidx_b;
	dm->dm_fat_table.antsel_rx_keep_2 = phy_sta_rpt->antidx_c;
	dm->dm_fat_table.antsel_rx_keep_3 = phy_sta_rpt->antidx_d;
}
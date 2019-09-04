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
struct phy_status_rpt_8812 {int r_RFMOD; int sub_chnl; } ;
struct dm_phy_status_info {int band_width; } ;
struct dm_per_pkt_info {scalar_t__ data_rate; } ;

/* Variables and functions */
 scalar_t__ ODM_RATE54M ; 

__attribute__((used)) static void
odm_rx_phy_bw_jaguar_series_parsing(struct dm_phy_status_info *phy_info,
				    struct dm_per_pkt_info *pktinfo,
				    struct phy_status_rpt_8812 *phy_sta_rpt)
{
	if (pktinfo->data_rate <= ODM_RATE54M) {
		switch (phy_sta_rpt->r_RFMOD) {
		case 1:
			if (phy_sta_rpt->sub_chnl == 0)
				phy_info->band_width = 1;
			else
				phy_info->band_width = 0;
			break;

		case 2:
			if (phy_sta_rpt->sub_chnl == 0)
				phy_info->band_width = 2;
			else if (phy_sta_rpt->sub_chnl == 9 ||
				 phy_sta_rpt->sub_chnl == 10)
				phy_info->band_width = 1;
			else
				phy_info->band_width = 0;
			break;

		default:
		case 0:
			phy_info->band_width = 0;
			break;
		}
	}
}
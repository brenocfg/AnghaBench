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
typedef  int u32 ;
struct phy_dm_struct {scalar_t__ is_linked; } ;

/* Variables and functions */
 int DM_DIG_FA_TH0 ; 
 int DM_DIG_FA_TH1 ; 
 int DM_DIG_FA_TH2 ; 

__attribute__((used)) static void odm_fa_threshold_check(void *dm_void, bool is_dfs_band,
				   bool is_performance, u32 rx_tp, u32 tx_tp,
				   u32 *dm_FA_thres)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;

	if (dm->is_linked && (is_performance || is_dfs_band)) {
		/*For NIC*/
		dm_FA_thres[0] = DM_DIG_FA_TH0;
		dm_FA_thres[1] = DM_DIG_FA_TH1;
		dm_FA_thres[2] = DM_DIG_FA_TH2;
	} else {
		if (is_dfs_band) {
			/* For DFS band and no link */
			dm_FA_thres[0] = 250;
			dm_FA_thres[1] = 1000;
			dm_FA_thres[2] = 2000;
		} else {
			dm_FA_thres[0] = 2000;
			dm_FA_thres[1] = 4000;
			dm_FA_thres[2] = 5000;
		}
	}
}
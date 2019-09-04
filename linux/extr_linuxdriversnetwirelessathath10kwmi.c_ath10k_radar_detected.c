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
struct ath10k {int /*<<< orphan*/  hw; scalar_t__ dfs_block_radar_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_REGULATORY ; 
 int /*<<< orphan*/  ATH10K_DFS_STAT_INC (struct ath10k*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_info (struct ath10k*,char*) ; 
 int /*<<< orphan*/  ieee80211_radar_detected (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radar_detected ; 

__attribute__((used)) static void ath10k_radar_detected(struct ath10k *ar)
{
	ath10k_dbg(ar, ATH10K_DBG_REGULATORY, "dfs radar detected\n");
	ATH10K_DFS_STAT_INC(ar, radar_detected);

	/* Control radar events reporting in debugfs file
	 * dfs_block_radar_events
	 */
	if (ar->dfs_block_radar_events)
		ath10k_info(ar, "DFS Radar detected, but ignored as requested\n");
	else
		ieee80211_radar_detected(ar->hw);
}
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
struct TYPE_2__ {int pri_margin; int /*<<< orphan*/  min_pri; int /*<<< orphan*/  max_pri; } ;
struct mt76x2_dfs_pattern_detector {int region; TYPE_1__ sw_dpd_params; } ;
struct mt76x2_dev {struct mt76x2_dfs_pattern_detector dfs_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_DFS_ETSI_MAX_PRI ; 
 int /*<<< orphan*/  MT_DFS_ETSI_MIN_PRI ; 
 int /*<<< orphan*/  MT_DFS_FCC_MAX_PRI ; 
 int /*<<< orphan*/  MT_DFS_FCC_MIN_PRI ; 
 int /*<<< orphan*/  MT_DFS_JP_MAX_PRI ; 
 int /*<<< orphan*/  MT_DFS_JP_MIN_PRI ; 
 int MT_DFS_PRI_MARGIN ; 
#define  NL80211_DFS_ETSI 131 
#define  NL80211_DFS_FCC 130 
#define  NL80211_DFS_JP 129 
#define  NL80211_DFS_UNSET 128 

__attribute__((used)) static void mt76x2_dfs_init_sw_detector(struct mt76x2_dev *dev)
{
	struct mt76x2_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;

	switch (dev->dfs_pd.region) {
	case NL80211_DFS_FCC:
		dfs_pd->sw_dpd_params.max_pri = MT_DFS_FCC_MAX_PRI;
		dfs_pd->sw_dpd_params.min_pri = MT_DFS_FCC_MIN_PRI;
		dfs_pd->sw_dpd_params.pri_margin = MT_DFS_PRI_MARGIN;
		break;
	case NL80211_DFS_ETSI:
		dfs_pd->sw_dpd_params.max_pri = MT_DFS_ETSI_MAX_PRI;
		dfs_pd->sw_dpd_params.min_pri = MT_DFS_ETSI_MIN_PRI;
		dfs_pd->sw_dpd_params.pri_margin = MT_DFS_PRI_MARGIN << 2;
		break;
	case NL80211_DFS_JP:
		dfs_pd->sw_dpd_params.max_pri = MT_DFS_JP_MAX_PRI;
		dfs_pd->sw_dpd_params.min_pri = MT_DFS_JP_MIN_PRI;
		dfs_pd->sw_dpd_params.pri_margin = MT_DFS_PRI_MARGIN;
		break;
	case NL80211_DFS_UNSET:
	default:
		break;
	}
}
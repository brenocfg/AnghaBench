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
struct mt76x2_dfs_pattern_detector {int region; int /*<<< orphan*/  dfs_tasklet; } ;
struct mt76x2_dev {struct mt76x2_dfs_pattern_detector dfs_pd; } ;
typedef  enum nl80211_dfs_regions { ____Placeholder_nl80211_dfs_regions } nl80211_dfs_regions ;

/* Variables and functions */
 int /*<<< orphan*/  mt76x2_dfs_init_params (struct mt76x2_dev*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

void mt76x2_dfs_set_domain(struct mt76x2_dev *dev,
			   enum nl80211_dfs_regions region)
{
	struct mt76x2_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;

	if (dfs_pd->region != region) {
		tasklet_disable(&dfs_pd->dfs_tasklet);
		dfs_pd->region = region;
		mt76x2_dfs_init_params(dev);
		tasklet_enable(&dfs_pd->dfs_tasklet);
	}
}
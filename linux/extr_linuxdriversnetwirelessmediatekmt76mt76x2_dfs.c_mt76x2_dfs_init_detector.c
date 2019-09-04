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
struct mt76x2_dfs_pattern_detector {int /*<<< orphan*/  dfs_tasklet; int /*<<< orphan*/  last_sw_check; int /*<<< orphan*/  region; int /*<<< orphan*/  seq_pool; int /*<<< orphan*/  sequences; } ;
struct mt76x2_dev {struct mt76x2_dfs_pattern_detector dfs_pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NL80211_DFS_UNSET ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mt76x2_dfs_tasklet ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

void mt76x2_dfs_init_detector(struct mt76x2_dev *dev)
{
	struct mt76x2_dfs_pattern_detector *dfs_pd = &dev->dfs_pd;

	INIT_LIST_HEAD(&dfs_pd->sequences);
	INIT_LIST_HEAD(&dfs_pd->seq_pool);
	dfs_pd->region = NL80211_DFS_UNSET;
	dfs_pd->last_sw_check = jiffies;
	tasklet_init(&dfs_pd->dfs_tasklet, mt76x2_dfs_tasklet,
		     (unsigned long)dev);
}
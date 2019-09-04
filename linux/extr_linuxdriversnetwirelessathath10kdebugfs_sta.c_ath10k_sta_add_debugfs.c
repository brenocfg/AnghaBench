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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct ieee80211_sta*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fops_addba ; 
 int /*<<< orphan*/  fops_addba_resp ; 
 int /*<<< orphan*/  fops_aggr_mode ; 
 int /*<<< orphan*/  fops_delba ; 
 int /*<<< orphan*/  fops_peer_debug_trigger ; 
 int /*<<< orphan*/  fops_tid_stats_dump ; 

void ath10k_sta_add_debugfs(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			    struct ieee80211_sta *sta, struct dentry *dir)
{
	debugfs_create_file("aggr_mode", 0644, dir, sta, &fops_aggr_mode);
	debugfs_create_file("addba", 0200, dir, sta, &fops_addba);
	debugfs_create_file("addba_resp", 0200, dir, sta, &fops_addba_resp);
	debugfs_create_file("delba", 0200, dir, sta, &fops_delba);
	debugfs_create_file("peer_debug_trigger", 0600, dir, sta,
			    &fops_peer_debug_trigger);
	debugfs_create_file("dump_tid_stats", 0400, dir, sta,
			    &fops_tid_stats_dump);
}
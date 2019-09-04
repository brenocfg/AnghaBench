#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  debugfs_dir; } ;
struct TYPE_6__ {int /*<<< orphan*/  default_mgmt_key; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; TYPE_3__ debugfs; int /*<<< orphan*/  default_mgmt_key; int /*<<< orphan*/  local; } ;
struct TYPE_5__ {int cnt; } ;
struct ieee80211_key {TYPE_2__ debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_symlink (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ieee80211_debugfs_key_remove_mgmt_default (struct ieee80211_sub_if_data*) ; 
 struct ieee80211_key* key_mtx_dereference (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

void ieee80211_debugfs_key_add_mgmt_default(struct ieee80211_sub_if_data *sdata)
{
	char buf[50];
	struct ieee80211_key *key;

	if (!sdata->vif.debugfs_dir)
		return;

	key = key_mtx_dereference(sdata->local,
				  sdata->default_mgmt_key);
	if (key) {
		sprintf(buf, "../keys/%d", key->debugfs.cnt);
		sdata->debugfs.default_mgmt_key =
			debugfs_create_symlink("default_mgmt_key",
					       sdata->vif.debugfs_dir, buf);
	} else
		ieee80211_debugfs_key_remove_mgmt_default(sdata);
}
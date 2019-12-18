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
struct TYPE_4__ {int /*<<< orphan*/ * subdir_stations; } ;
struct TYPE_3__ {int /*<<< orphan*/ * debugfs_dir; } ;
struct ieee80211_sub_if_data {TYPE_2__ debugfs; TYPE_1__ vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 

void ieee80211_debugfs_remove_netdev(struct ieee80211_sub_if_data *sdata)
{
	if (!sdata->vif.debugfs_dir)
		return;

	debugfs_remove_recursive(sdata->vif.debugfs_dir);
	sdata->vif.debugfs_dir = NULL;
	sdata->debugfs.subdir_stations = NULL;
}
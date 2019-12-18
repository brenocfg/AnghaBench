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
struct TYPE_2__ {int /*<<< orphan*/  debugfs_dir; } ;
struct ieee80211_sub_if_data {TYPE_1__ vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_create_file (char*,int,int /*<<< orphan*/ ,struct ieee80211_sub_if_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_mcast_sta_vlan_ops ; 

__attribute__((used)) static void add_vlan_files(struct ieee80211_sub_if_data *sdata)
{
	/* add num_mcast_sta_vlan using name num_mcast_sta */
	debugfs_create_file("num_mcast_sta", 0400, sdata->vif.debugfs_dir,
			    sdata, &num_mcast_sta_vlan_ops);
}
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
struct ieee80211_sub_if_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGFS_ADD_MODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aid ; 
 int /*<<< orphan*/  beacon_loss ; 
 int /*<<< orphan*/  beacon_timeout ; 
 int /*<<< orphan*/  bssid ; 
 int /*<<< orphan*/  smps ; 
 int /*<<< orphan*/  tdls_wider_bw ; 
 int /*<<< orphan*/  tkip_mic_test ; 
 int /*<<< orphan*/  uapsd_max_sp_len ; 
 int /*<<< orphan*/  uapsd_queues ; 

__attribute__((used)) static void add_sta_files(struct ieee80211_sub_if_data *sdata)
{
	DEBUGFS_ADD(bssid);
	DEBUGFS_ADD(aid);
	DEBUGFS_ADD(beacon_timeout);
	DEBUGFS_ADD_MODE(smps, 0600);
	DEBUGFS_ADD_MODE(tkip_mic_test, 0200);
	DEBUGFS_ADD_MODE(beacon_loss, 0200);
	DEBUGFS_ADD_MODE(uapsd_queues, 0600);
	DEBUGFS_ADD_MODE(uapsd_max_sp_len, 0600);
	DEBUGFS_ADD_MODE(tdls_wider_bw, 0600);
}
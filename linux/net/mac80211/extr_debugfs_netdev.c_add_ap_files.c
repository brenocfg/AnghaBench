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
 int /*<<< orphan*/  dtim_count ; 
 int /*<<< orphan*/  multicast_to_unicast ; 
 int /*<<< orphan*/  num_buffered_multicast ; 
 int /*<<< orphan*/  num_mcast_sta ; 
 int /*<<< orphan*/  num_sta_ps ; 
 int /*<<< orphan*/  smps ; 
 int /*<<< orphan*/  tkip_mic_test ; 

__attribute__((used)) static void add_ap_files(struct ieee80211_sub_if_data *sdata)
{
	DEBUGFS_ADD(num_mcast_sta);
	DEBUGFS_ADD_MODE(smps, 0600);
	DEBUGFS_ADD(num_sta_ps);
	DEBUGFS_ADD(dtim_count);
	DEBUGFS_ADD(num_buffered_multicast);
	DEBUGFS_ADD_MODE(tkip_mic_test, 0200);
	DEBUGFS_ADD_MODE(multicast_to_unicast, 0600);
}
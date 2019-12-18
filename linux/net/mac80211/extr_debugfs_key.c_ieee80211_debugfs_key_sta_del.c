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
struct sta_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * stalink; } ;
struct ieee80211_key {TYPE_1__ debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 

void ieee80211_debugfs_key_sta_del(struct ieee80211_key *key,
				   struct sta_info *sta)
{
	debugfs_remove(key->debugfs.stalink);
	key->debugfs.stalink = NULL;
}
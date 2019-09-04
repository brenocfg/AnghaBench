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
struct sta_info {TYPE_1__* mesh; } ;
struct ieee80211_tx_status {struct ieee80211_tx_info* info; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_local {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fail_avg; } ;

/* Variables and functions */
 int IEEE80211_TX_STAT_ACK ; 
 scalar_t__ LINK_FAIL_THRESH ; 
 int /*<<< orphan*/  ewma_mesh_fail_avg_add (int /*<<< orphan*/ *,int) ; 
 scalar_t__ ewma_mesh_fail_avg_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_plink_broken (struct sta_info*) ; 

void ieee80211s_update_metric(struct ieee80211_local *local,
			      struct sta_info *sta,
			      struct ieee80211_tx_status *st)
{
	struct ieee80211_tx_info *txinfo = st->info;
	int failed;

	failed = !(txinfo->flags & IEEE80211_TX_STAT_ACK);

	/* moving average, scaled to 100.
	 * feed failure as 100 and success as 0
	 */
	ewma_mesh_fail_avg_add(&sta->mesh->fail_avg, failed * 100);
	if (ewma_mesh_fail_avg_read(&sta->mesh->fail_avg) >
			LINK_FAIL_THRESH)
		mesh_plink_broken(sta);
}
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
struct ath6kl_vif {struct ath6kl* ar; } ;
struct ath6kl {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int __ath6kl_cfg80211_sscan_stop (struct ath6kl_vif*) ; 
 int /*<<< orphan*/  cfg80211_sched_scan_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath6kl_cfg80211_sscan_disable(struct ath6kl_vif *vif)
{
	struct ath6kl *ar = vif->ar;
	bool stopped;

	stopped = __ath6kl_cfg80211_sscan_stop(vif);

	if (!stopped)
		return;

	cfg80211_sched_scan_stopped(ar->wiphy, 0);
}
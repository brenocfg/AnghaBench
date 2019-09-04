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
struct timer_list {int dummy; } ;
struct ath6kl_vif {TYPE_1__* ar; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cfg80211_sched_scan_results (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath6kl_vif* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_scan_timer ; 
 struct ath6kl_vif* vif ; 

void ath6kl_wmi_sscan_timer(struct timer_list *t)
{
	struct ath6kl_vif *vif = from_timer(vif, t, sched_scan_timer);

	cfg80211_sched_scan_results(vif->ar->wiphy, 0);
}
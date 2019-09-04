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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_5__ {TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_3__* local; TYPE_2__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_STA_CONNECTION_POLL ; 
 int /*<<< orphan*/  ieee80211_run_deferred_scan (TYPE_3__*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __ieee80211_stop_poll(struct ieee80211_sub_if_data *sdata)
{
	lockdep_assert_held(&sdata->local->mtx);

	sdata->u.mgd.flags &= ~IEEE80211_STA_CONNECTION_POLL;
	ieee80211_run_deferred_scan(sdata->local);
}
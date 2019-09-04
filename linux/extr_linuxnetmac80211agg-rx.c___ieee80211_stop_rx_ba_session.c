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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  mtx; } ;
struct sta_info {TYPE_1__ ampdu_mlme; } ;

/* Variables and functions */
 int /*<<< orphan*/  ___ieee80211_stop_rx_ba_session (struct sta_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void __ieee80211_stop_rx_ba_session(struct sta_info *sta, u16 tid,
				    u16 initiator, u16 reason, bool tx)
{
	mutex_lock(&sta->ampdu_mlme.mtx);
	___ieee80211_stop_rx_ba_session(sta, tid, initiator, reason, tx);
	mutex_unlock(&sta->ampdu_mlme.mtx);
}
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
typedef  int /*<<< orphan*/  u8 ;
struct timer_list {int dummy; } ;
struct tid_ampdu_rx {unsigned long last_rx; int /*<<< orphan*/  session_timer; int /*<<< orphan*/  timeout; int /*<<< orphan*/  tid; struct sta_info* sta; } ;
struct TYPE_6__ {int /*<<< orphan*/  work; int /*<<< orphan*/  tid_rx_timer_expired; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_3__ ampdu_mlme; TYPE_2__* local; TYPE_1__ sta; int /*<<< orphan*/  sdata; } ;
struct TYPE_5__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 unsigned long TU_TO_JIFFIES (int /*<<< orphan*/ ) ; 
 struct tid_ampdu_rx* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ht_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  session_timer ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tid_ampdu_rx* tid_rx ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 

__attribute__((used)) static void sta_rx_agg_session_timer_expired(struct timer_list *t)
{
	struct tid_ampdu_rx *tid_rx = from_timer(tid_rx, t, session_timer);
	struct sta_info *sta = tid_rx->sta;
	u8 tid = tid_rx->tid;
	unsigned long timeout;

	timeout = tid_rx->last_rx + TU_TO_JIFFIES(tid_rx->timeout);
	if (time_is_after_jiffies(timeout)) {
		mod_timer(&tid_rx->session_timer, timeout);
		return;
	}

	ht_dbg(sta->sdata, "RX session timer expired on %pM tid %d\n",
	       sta->sta.addr, tid);

	set_bit(tid, sta->ampdu_mlme.tid_rx_timer_expired);
	ieee80211_queue_work(&sta->local->hw, &sta->ampdu_mlme.work);
}
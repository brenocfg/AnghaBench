#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct tid_ampdu_tx {int bar_pending; int /*<<< orphan*/  failed_bar_ssn; } ;
struct TYPE_3__ {int /*<<< orphan*/ * tid_tx; } ;
struct sta_info {TYPE_2__* sdata; TYPE_1__ ampdu_mlme; } ;
struct TYPE_4__ {int /*<<< orphan*/  vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_send_bar (int /*<<< orphan*/ *,size_t*,size_t,int /*<<< orphan*/ ) ; 
 struct tid_ampdu_tx* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_check_pending_bar(struct sta_info *sta, u8 *addr, u8 tid)
{
	struct tid_ampdu_tx *tid_tx;

	tid_tx = rcu_dereference(sta->ampdu_mlme.tid_tx[tid]);
	if (!tid_tx || !tid_tx->bar_pending)
		return;

	tid_tx->bar_pending = false;
	ieee80211_send_bar(&sta->sdata->vif, addr, tid, tid_tx->failed_bar_ssn);
}
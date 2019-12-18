#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int tid; TYPE_3__* sta; int /*<<< orphan*/  ac; TYPE_1__* vif; } ;
struct txq_info {TYPE_4__ txq; int /*<<< orphan*/  schedule_order; int /*<<< orphan*/  frags; int /*<<< orphan*/  cstats; int /*<<< orphan*/  def_cvars; int /*<<< orphan*/  def_flow; int /*<<< orphan*/  tin; } ;
struct TYPE_7__ {TYPE_4__** txq; } ;
struct sta_info {TYPE_3__ sta; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_4__* txq; } ;
struct ieee80211_sub_if_data {TYPE_2__* local; TYPE_1__ vif; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFF_MMPDU_TXQ ; 
 int /*<<< orphan*/  IEEE80211_AC_BE ; 
 int /*<<< orphan*/  IEEE80211_AC_VO ; 
 int IEEE80211_NUM_TIDS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  STA_MMPDU_TXQ ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  codel_stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  codel_vars_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fq_flow_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fq_tin_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ac_from_tid (int) ; 
 int /*<<< orphan*/  ieee80211_hw_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ieee80211_txq_init(struct ieee80211_sub_if_data *sdata,
			struct sta_info *sta,
			struct txq_info *txqi, int tid)
{
	fq_tin_init(&txqi->tin);
	fq_flow_init(&txqi->def_flow);
	codel_vars_init(&txqi->def_cvars);
	codel_stats_init(&txqi->cstats);
	__skb_queue_head_init(&txqi->frags);
	INIT_LIST_HEAD(&txqi->schedule_order);

	txqi->txq.vif = &sdata->vif;

	if (!sta) {
		sdata->vif.txq = &txqi->txq;
		txqi->txq.tid = 0;
		txqi->txq.ac = IEEE80211_AC_BE;

		return;
	}

	if (tid == IEEE80211_NUM_TIDS) {
		if (sdata->vif.type == NL80211_IFTYPE_STATION) {
			/* Drivers need to opt in to the management MPDU TXQ */
			if (!ieee80211_hw_check(&sdata->local->hw,
						STA_MMPDU_TXQ))
				return;
		} else if (!ieee80211_hw_check(&sdata->local->hw,
					       BUFF_MMPDU_TXQ)) {
			/* Drivers need to opt in to the bufferable MMPDU TXQ */
			return;
		}
		txqi->txq.ac = IEEE80211_AC_VO;
	} else {
		txqi->txq.ac = ieee80211_ac_from_tid(tid);
	}

	txqi->txq.sta = &sta->sta;
	txqi->txq.tid = tid;
	sta->sta.txq[tid] = &txqi->txq;
}
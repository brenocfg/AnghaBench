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
struct TYPE_6__ {int tid; int /*<<< orphan*/  ac; TYPE_1__* sta; TYPE_2__* vif; } ;
struct txq_info {TYPE_3__ txq; int /*<<< orphan*/  frags; int /*<<< orphan*/  cstats; int /*<<< orphan*/  def_cvars; int /*<<< orphan*/  def_flow; int /*<<< orphan*/  tin; } ;
struct TYPE_4__ {TYPE_3__** txq; } ;
struct sta_info {TYPE_1__ sta; } ;
struct TYPE_5__ {TYPE_3__* txq; } ;
struct ieee80211_sub_if_data {TYPE_2__ vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_AC_BE ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  codel_stats_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  codel_vars_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fq_flow_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fq_tin_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ac_from_tid (int) ; 

void ieee80211_txq_init(struct ieee80211_sub_if_data *sdata,
			struct sta_info *sta,
			struct txq_info *txqi, int tid)
{
	fq_tin_init(&txqi->tin);
	fq_flow_init(&txqi->def_flow);
	codel_vars_init(&txqi->def_cvars);
	codel_stats_init(&txqi->cstats);
	__skb_queue_head_init(&txqi->frags);

	txqi->txq.vif = &sdata->vif;

	if (sta) {
		txqi->txq.sta = &sta->sta;
		sta->sta.txq[tid] = &txqi->txq;
		txqi->txq.tid = tid;
		txqi->txq.ac = ieee80211_ac_from_tid(tid);
	} else {
		sdata->vif.txq = &txqi->txq;
		txqi->txq.tid = 0;
		txqi->txq.ac = IEEE80211_AC_BE;
	}
}
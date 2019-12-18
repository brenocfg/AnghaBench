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
typedef  int u32 ;
struct minstrel_ht_sta {int* max_tp_rate; TYPE_2__* groups; } ;
struct minstrel_ht_sta_priv {int /*<<< orphan*/  is_ht; struct minstrel_ht_sta ht; } ;
struct TYPE_6__ {int (* get_expected_throughput ) (void*) ;} ;
struct TYPE_5__ {TYPE_1__* rates; } ;
struct TYPE_4__ {int prob_ewma; } ;

/* Variables and functions */
 int AVG_PKT_SIZE ; 
 int MCS_GROUP_RATES ; 
 TYPE_3__ mac80211_minstrel ; 
 int minstrel_ht_get_tp_avg (struct minstrel_ht_sta*,int,int,int) ; 
 int stub1 (void*) ; 

__attribute__((used)) static u32 minstrel_ht_get_expected_throughput(void *priv_sta)
{
	struct minstrel_ht_sta_priv *msp = priv_sta;
	struct minstrel_ht_sta *mi = &msp->ht;
	int i, j, prob, tp_avg;

	if (!msp->is_ht)
		return mac80211_minstrel.get_expected_throughput(priv_sta);

	i = mi->max_tp_rate[0] / MCS_GROUP_RATES;
	j = mi->max_tp_rate[0] % MCS_GROUP_RATES;
	prob = mi->groups[i].rates[j].prob_ewma;

	/* convert tp_avg from pkt per second in kbps */
	tp_avg = minstrel_ht_get_tp_avg(mi, i, j, prob) * 10;
	tp_avg = tp_avg * AVG_PKT_SIZE * 8 / 1024;

	return tp_avg;
}
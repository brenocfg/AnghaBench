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
struct minstrel_ht_sta {int max_prob_rate; TYPE_4__* sta; int /*<<< orphan*/ * max_tp_rate; TYPE_2__* groups; } ;
struct mcs_group {unsigned int* duration; unsigned int shift; } ;
struct TYPE_7__ {int /*<<< orphan*/  vht_supported; } ;
struct TYPE_8__ {TYPE_3__ vht_cap; } ;
struct TYPE_6__ {TYPE_1__* rates; } ;
struct TYPE_5__ {scalar_t__ prob_ewma; } ;

/* Variables and functions */
 int IEEE80211_MAX_MPDU_LEN_HT_BA ; 
 unsigned int MCS_DURATION (int,int /*<<< orphan*/ ,int) ; 
 int MCS_GROUP_RATES ; 
 scalar_t__ MINSTREL_FRAC (int,int) ; 
 scalar_t__ minstrel_ht_get_prob_ewma (struct minstrel_ht_sta*,int /*<<< orphan*/ ) ; 
 struct mcs_group* minstrel_mcs_groups ; 

__attribute__((used)) static int
minstrel_ht_get_max_amsdu_len(struct minstrel_ht_sta *mi)
{
	int group = mi->max_prob_rate / MCS_GROUP_RATES;
	const struct mcs_group *g = &minstrel_mcs_groups[group];
	int rate = mi->max_prob_rate % MCS_GROUP_RATES;
	unsigned int duration;

	/* Disable A-MSDU if max_prob_rate is bad */
	if (mi->groups[group].rates[rate].prob_ewma < MINSTREL_FRAC(50, 100))
		return 1;

	duration = g->duration[rate];
	duration <<= g->shift;

	/* If the rate is slower than single-stream MCS1, make A-MSDU limit small */
	if (duration > MCS_DURATION(1, 0, 52))
		return 500;

	/*
	 * If the rate is slower than single-stream MCS4, limit A-MSDU to usual
	 * data packet size
	 */
	if (duration > MCS_DURATION(1, 0, 104))
		return 1600;

	/*
	 * If the rate is slower than single-stream MCS7, or if the max throughput
	 * rate success probability is less than 75%, limit A-MSDU to twice the usual
	 * data packet size
	 */
	if (duration > MCS_DURATION(1, 0, 260) ||
	    (minstrel_ht_get_prob_ewma(mi, mi->max_tp_rate[0]) <
	     MINSTREL_FRAC(75, 100)))
		return 3200;

	/*
	 * HT A-MPDU limits maximum MPDU size under BA agreement to 4095 bytes.
	 * Since aggregation sessions are started/stopped without txq flush, use
	 * the limit here to avoid the complexity of having to de-aggregate
	 * packets in the queue.
	 */
	if (!mi->sta->vht_cap.vht_supported)
		return IEEE80211_MAX_MPDU_LEN_HT_BA;

	/* unlimited */
	return 0;
}
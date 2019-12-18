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
struct minstrel_ht_sta {int overhead; } ;
struct TYPE_2__ {unsigned int* duration; unsigned int shift; } ;

/* Variables and functions */
 int MINSTREL_CCK_GROUP ; 
 int MINSTREL_FRAC (int,int) ; 
 int MINSTREL_TRUNC (int) ; 
 int minstrel_ht_avg_ampdu_len (struct minstrel_ht_sta*) ; 
 TYPE_1__* minstrel_mcs_groups ; 

int
minstrel_ht_get_tp_avg(struct minstrel_ht_sta *mi, int group, int rate,
		       int prob_ewma)
{
	unsigned int nsecs = 0;

	/* do not account throughput if sucess prob is below 10% */
	if (prob_ewma < MINSTREL_FRAC(10, 100))
		return 0;

	if (group != MINSTREL_CCK_GROUP)
		nsecs = 1000 * mi->overhead / minstrel_ht_avg_ampdu_len(mi);

	nsecs += minstrel_mcs_groups[group].duration[rate] <<
		 minstrel_mcs_groups[group].shift;

	/*
	 * For the throughput calculation, limit the probability value to 90% to
	 * account for collision related packet error rate fluctuation
	 * (prob is scaled - see MINSTREL_FRAC above)
	 */
	if (prob_ewma > MINSTREL_FRAC(90, 100))
		return MINSTREL_TRUNC(100000 * ((MINSTREL_FRAC(90, 100) * 1000)
								      / nsecs));
	else
		return MINSTREL_TRUNC(100000 * ((prob_ewma * 1000) / nsecs));
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct minstrel_rate_stats {scalar_t__ attempts; scalar_t__ att_hist; unsigned int prob_ewma; scalar_t__ last_attempts; scalar_t__ success; scalar_t__ last_success; scalar_t__ sample_skipped; int /*<<< orphan*/  succ_hist; } ;

/* Variables and functions */
 int /*<<< orphan*/  EWMA_LEVEL ; 
 unsigned int MINSTREL_FRAC (scalar_t__,scalar_t__) ; 
 unsigned int minstrel_ewma (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void
minstrel_calc_rate_stats(struct minstrel_rate_stats *mrs)
{
	unsigned int cur_prob;

	if (unlikely(mrs->attempts > 0)) {
		mrs->sample_skipped = 0;
		cur_prob = MINSTREL_FRAC(mrs->success, mrs->attempts);
		if (unlikely(!mrs->att_hist)) {
			mrs->prob_ewma = cur_prob;
		} else {
			/*update exponential weighted moving avarage */
			mrs->prob_ewma = minstrel_ewma(mrs->prob_ewma,
						       cur_prob,
						       EWMA_LEVEL);
		}
		mrs->att_hist += mrs->attempts;
		mrs->succ_hist += mrs->success;
	} else {
		mrs->sample_skipped++;
	}

	mrs->last_success = mrs->success;
	mrs->last_attempts = mrs->attempts;
	mrs->success = 0;
	mrs->attempts = 0;
}
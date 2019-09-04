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
typedef  scalar_t__ u32 ;
struct sfb_sched_data {size_t slot; TYPE_1__* bins; } ;
struct sfb_bucket {scalar_t__ qlen; scalar_t__ p_mark; } ;
struct TYPE_2__ {struct sfb_bucket** bins; } ;

/* Variables and functions */
 int SFB_LEVELS ; 
 int SFB_NUMBUCKETS ; 

__attribute__((used)) static u32 sfb_compute_qlen(u32 *prob_r, u32 *avgpm_r, const struct sfb_sched_data *q)
{
	int i;
	u32 qlen = 0, prob = 0, totalpm = 0;
	const struct sfb_bucket *b = &q->bins[q->slot].bins[0][0];

	for (i = 0; i < SFB_LEVELS * SFB_NUMBUCKETS; i++) {
		if (qlen < b->qlen)
			qlen = b->qlen;
		totalpm += b->p_mark;
		if (prob < b->p_mark)
			prob = b->p_mark;
		b++;
	}
	*prob_r = prob;
	*avgpm_r = totalpm / (SFB_LEVELS * SFB_NUMBUCKETS);
	return qlen;
}
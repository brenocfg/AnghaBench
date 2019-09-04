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
typedef  size_t u64 ;
struct cyc_hist {int num_aggr; int cycles_aggr; int /*<<< orphan*/  cycles_min; int /*<<< orphan*/  cycles_max; int /*<<< orphan*/  start; scalar_t__ have_start; scalar_t__ cycles; } ;
struct annotation_line {int cycles; int /*<<< orphan*/  cycles_min; int /*<<< orphan*/  cycles_max; } ;
struct annotation {int have_cycles; int /*<<< orphan*/  lock; struct annotation_line** offsets; TYPE_1__* src; } ;
struct TYPE_2__ {struct cyc_hist* cycles_hist; } ;

/* Variables and functions */
 int /*<<< orphan*/  annotation__count_and_fill (struct annotation*,int /*<<< orphan*/ ,size_t,struct cyc_hist*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

void annotation__compute_ipc(struct annotation *notes, size_t size)
{
	u64 offset;

	if (!notes->src || !notes->src->cycles_hist)
		return;

	pthread_mutex_lock(&notes->lock);
	for (offset = 0; offset < size; ++offset) {
		struct cyc_hist *ch;

		ch = &notes->src->cycles_hist[offset];
		if (ch && ch->cycles) {
			struct annotation_line *al;

			if (ch->have_start)
				annotation__count_and_fill(notes, ch->start, offset, ch);
			al = notes->offsets[offset];
			if (al && ch->num_aggr) {
				al->cycles = ch->cycles_aggr / ch->num_aggr;
				al->cycles_max = ch->cycles_max;
				al->cycles_min = ch->cycles_min;
			}
			notes->have_cycles = true;
		}
	}
	pthread_mutex_unlock(&notes->lock);
}
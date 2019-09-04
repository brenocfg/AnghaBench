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
typedef  size_t u64 ;
struct cyc_hist {int num; int reset; scalar_t__ cycles; } ;
struct annotation_line {float ipc; } ;
struct annotation {struct annotation_line** offsets; } ;

/* Variables and functions */
 unsigned int annotation__count_insn (struct annotation*,size_t,size_t) ; 

__attribute__((used)) static void annotation__count_and_fill(struct annotation *notes, u64 start, u64 end, struct cyc_hist *ch)
{
	unsigned n_insn;
	u64 offset;

	n_insn = annotation__count_insn(notes, start, end);
	if (n_insn && ch->num && ch->cycles) {
		float ipc = n_insn / ((double)ch->cycles / (double)ch->num);

		/* Hide data when there are too many overlaps. */
		if (ch->reset >= 0x7fff || ch->reset >= ch->num / 2)
			return;

		for (offset = start; offset <= end; offset++) {
			struct annotation_line *al = notes->offsets[offset];

			if (al)
				al->ipc = ipc;
		}
	}
}
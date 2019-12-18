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
struct cyc_hist {unsigned int num; int reset; scalar_t__ cycles; } ;
struct annotation_line {double ipc; } ;
struct annotation {unsigned int hit_insn; unsigned int cover_insn; int /*<<< orphan*/  hit_cycles; struct annotation_line** offsets; } ;

/* Variables and functions */
 unsigned int annotation__count_insn (struct annotation*,size_t,size_t) ; 

__attribute__((used)) static void annotation__count_and_fill(struct annotation *notes, u64 start, u64 end, struct cyc_hist *ch)
{
	unsigned n_insn;
	unsigned int cover_insn = 0;
	u64 offset;

	n_insn = annotation__count_insn(notes, start, end);
	if (n_insn && ch->num && ch->cycles) {
		float ipc = n_insn / ((double)ch->cycles / (double)ch->num);

		/* Hide data when there are too many overlaps. */
		if (ch->reset >= 0x7fff)
			return;

		for (offset = start; offset <= end; offset++) {
			struct annotation_line *al = notes->offsets[offset];

			if (al && al->ipc == 0.0) {
				al->ipc = ipc;
				cover_insn++;
			}
		}

		if (cover_insn) {
			notes->hit_cycles += ch->cycles;
			notes->hit_insn += n_insn * ch->num;
			notes->cover_insn += cover_insn;
		}
	}
}
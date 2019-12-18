#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int last_syt_offset; unsigned int syt_offset_state; scalar_t__ transfer_delay; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct amdtp_stream {TYPE_2__ ctx_data; int /*<<< orphan*/  sfc; } ;

/* Variables and functions */
 unsigned int CIP_SYT_MASK ; 
 unsigned int CIP_SYT_NO_INFO ; 
 unsigned int TICKS_PER_CYCLE ; 
 int /*<<< orphan*/  cip_sfc_is_base_44100 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int calculate_syt(struct amdtp_stream *s,
				  unsigned int cycle)
{
	unsigned int syt_offset, phase, index, syt;

	if (s->ctx_data.rx.last_syt_offset < TICKS_PER_CYCLE) {
		if (!cip_sfc_is_base_44100(s->sfc))
			syt_offset = s->ctx_data.rx.last_syt_offset +
				     s->ctx_data.rx.syt_offset_state;
		else {
		/*
		 * The time, in ticks, of the n'th SYT_INTERVAL sample is:
		 *   n * SYT_INTERVAL * 24576000 / sample_rate
		 * Modulo TICKS_PER_CYCLE, the difference between successive
		 * elements is about 1386.23.  Rounding the results of this
		 * formula to the SYT precision results in a sequence of
		 * differences that begins with:
		 *   1386 1386 1387 1386 1386 1386 1387 1386 1386 1386 1387 ...
		 * This code generates _exactly_ the same sequence.
		 */
			phase = s->ctx_data.rx.syt_offset_state;
			index = phase % 13;
			syt_offset = s->ctx_data.rx.last_syt_offset;
			syt_offset += 1386 + ((index && !(index & 3)) ||
					      phase == 146);
			if (++phase >= 147)
				phase = 0;
			s->ctx_data.rx.syt_offset_state = phase;
		}
	} else
		syt_offset = s->ctx_data.rx.last_syt_offset - TICKS_PER_CYCLE;
	s->ctx_data.rx.last_syt_offset = syt_offset;

	if (syt_offset < TICKS_PER_CYCLE) {
		syt_offset += s->ctx_data.rx.transfer_delay;
		syt = (cycle + syt_offset / TICKS_PER_CYCLE) << 12;
		syt += syt_offset % TICKS_PER_CYCLE;

		return syt & CIP_SYT_MASK;
	} else {
		return CIP_SYT_NO_INFO;
	}
}
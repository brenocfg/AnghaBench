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
struct TYPE_3__ {unsigned int data_block_state; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct amdtp_stream {int flags; unsigned int syt_interval; int sfc; TYPE_2__ ctx_data; } ;

/* Variables and functions */
 int CIP_BLOCKING ; 
 int CIP_SFC_44100 ; 
 unsigned int CIP_SYT_NO_INFO ; 
 int /*<<< orphan*/  cip_sfc_is_base_44100 (int) ; 

__attribute__((used)) static unsigned int calculate_data_blocks(struct amdtp_stream *s,
					  unsigned int syt)
{
	unsigned int phase, data_blocks;

	/* Blocking mode. */
	if (s->flags & CIP_BLOCKING) {
		/* This module generate empty packet for 'no data'. */
		if (syt == CIP_SYT_NO_INFO)
			data_blocks = 0;
		else
			data_blocks = s->syt_interval;
	/* Non-blocking mode. */
	} else {
		if (!cip_sfc_is_base_44100(s->sfc)) {
			// Sample_rate / 8000 is an integer, and precomputed.
			data_blocks = s->ctx_data.rx.data_block_state;
		} else {
			phase = s->ctx_data.rx.data_block_state;

		/*
		 * This calculates the number of data blocks per packet so that
		 * 1) the overall rate is correct and exactly synchronized to
		 *    the bus clock, and
		 * 2) packets with a rounded-up number of blocks occur as early
		 *    as possible in the sequence (to prevent underruns of the
		 *    device's buffer).
		 */
			if (s->sfc == CIP_SFC_44100)
				/* 6 6 5 6 5 6 5 ... */
				data_blocks = 5 + ((phase & 1) ^
						   (phase == 0 || phase >= 40));
			else
				/* 12 11 11 11 11 ... or 23 22 22 22 22 ... */
				data_blocks = 11 * (s->sfc >> 1) + (phase == 0);
			if (++phase >= (80 >> (s->sfc >> 1)))
				phase = 0;
			s->ctx_data.rx.data_block_state = phase;
		}
	}

	return data_blocks;
}
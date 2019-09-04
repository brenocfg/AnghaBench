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
struct amdtp_stream {unsigned int sfc; unsigned int data_block_quadlets; unsigned int syt_interval; int flags; scalar_t__ transfer_delay; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned int*) ; 
 int CIP_BLOCKING ; 
 int EINVAL ; 
 scalar_t__ TICKS_PER_CYCLE ; 
 unsigned int TICKS_PER_SECOND ; 
 scalar_t__ TRANSFER_DELAY_TICKS ; 
 unsigned int* amdtp_rate_table ; 
 unsigned int* amdtp_syt_intervals ; 

int amdtp_stream_set_parameters(struct amdtp_stream *s, unsigned int rate,
				unsigned int data_block_quadlets)
{
	unsigned int sfc;

	for (sfc = 0; sfc < ARRAY_SIZE(amdtp_rate_table); ++sfc) {
		if (amdtp_rate_table[sfc] == rate)
			break;
	}
	if (sfc == ARRAY_SIZE(amdtp_rate_table))
		return -EINVAL;

	s->sfc = sfc;
	s->data_block_quadlets = data_block_quadlets;
	s->syt_interval = amdtp_syt_intervals[sfc];

	/* default buffering in the device */
	s->transfer_delay = TRANSFER_DELAY_TICKS - TICKS_PER_CYCLE;
	if (s->flags & CIP_BLOCKING)
		/* additional buffering needed to adjust for no-data packets */
		s->transfer_delay += TICKS_PER_SECOND * s->syt_interval / rate;

	return 0;
}
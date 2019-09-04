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
typedef  unsigned long long uint64_t ;
struct obs_encoder {size_t blocksize; scalar_t__ samplerate; } ;

/* Variables and functions */

__attribute__((used)) static inline size_t calc_offset_size(struct obs_encoder *encoder,
		uint64_t v_start_ts, uint64_t a_start_ts)
{
	uint64_t offset = v_start_ts - a_start_ts;
	offset = (uint64_t)offset * (uint64_t)encoder->samplerate /
		1000000000ULL;
	return (size_t)offset * encoder->blocksize;
}
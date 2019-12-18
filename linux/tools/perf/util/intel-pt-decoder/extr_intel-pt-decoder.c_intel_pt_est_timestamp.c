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
typedef  int uint64_t ;
struct intel_pt_decoder {int sample_insn_cnt; int cbr; int max_non_turbo_ratio; int sample_timestamp; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t intel_pt_est_timestamp(struct intel_pt_decoder *decoder)
{
	uint64_t est = decoder->sample_insn_cnt << 1;

	if (!decoder->cbr || !decoder->max_non_turbo_ratio)
		goto out;

	est *= decoder->max_non_turbo_ratio;
	est /= decoder->cbr;
out:
	return decoder->sample_timestamp + est;
}
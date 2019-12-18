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
typedef  scalar_t__ uint64_t ;
struct intel_pt_decoder {int sample_cyc; scalar_t__ timestamp; scalar_t__ cyc_cnt_timestamp; scalar_t__ tsc_to_cyc; scalar_t__ base_cyc_cnt; scalar_t__ tot_cyc_cnt; int /*<<< orphan*/  pge; scalar_t__ have_cyc; } ;

/* Variables and functions */

__attribute__((used)) static inline void intel_pt_mtc_cyc_cnt_upd(struct intel_pt_decoder *decoder)
{
	uint64_t tot_cyc_cnt, tsc_delta;

	if (decoder->have_cyc)
		return;

	decoder->sample_cyc = true;

	if (!decoder->pge || decoder->timestamp <= decoder->cyc_cnt_timestamp)
		return;

	tsc_delta = decoder->timestamp - decoder->cyc_cnt_timestamp;
	tot_cyc_cnt = tsc_delta * decoder->tsc_to_cyc + decoder->base_cyc_cnt;

	if (tot_cyc_cnt > decoder->tot_cyc_cnt)
		decoder->tot_cyc_cnt = tot_cyc_cnt;
}
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
struct intel_pt_decoder {int /*<<< orphan*/  tot_cyc_cnt; int /*<<< orphan*/  base_cyc_cnt; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  cyc_cnt_timestamp; scalar_t__ have_cyc; } ;

/* Variables and functions */

__attribute__((used)) static inline void intel_pt_mtc_cyc_cnt_pge(struct intel_pt_decoder *decoder)
{
	if (decoder->have_cyc)
		return;

	decoder->cyc_cnt_timestamp = decoder->timestamp;
	decoder->base_cyc_cnt = decoder->tot_cyc_cnt;
}
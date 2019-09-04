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
struct intel_pt_decoder {int /*<<< orphan*/  fixup_last_mtc; int /*<<< orphan*/  have_tma; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  tsc_timestamp; int /*<<< orphan*/  ctc_delta; int /*<<< orphan*/  ctc_timestamp; int /*<<< orphan*/  last_mtc; } ;
struct intel_pt_calc_cyc_to_tsc_info {int from_mtc; int /*<<< orphan*/  cbr_cyc_to_tsc; int /*<<< orphan*/  fixup_last_mtc; int /*<<< orphan*/  have_tma; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  tsc_timestamp; int /*<<< orphan*/  ctc_delta; int /*<<< orphan*/  ctc_timestamp; int /*<<< orphan*/  last_mtc; int /*<<< orphan*/  cbr; int /*<<< orphan*/  cycle_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_calc_cyc_cb ; 
 int /*<<< orphan*/  intel_pt_pkt_lookahead (struct intel_pt_decoder*,int /*<<< orphan*/ ,struct intel_pt_calc_cyc_to_tsc_info*) ; 

__attribute__((used)) static void intel_pt_calc_cyc_to_tsc(struct intel_pt_decoder *decoder,
				     bool from_mtc)
{
	struct intel_pt_calc_cyc_to_tsc_info data = {
		.cycle_cnt      = 0,
		.cbr            = 0,
		.last_mtc       = decoder->last_mtc,
		.ctc_timestamp  = decoder->ctc_timestamp,
		.ctc_delta      = decoder->ctc_delta,
		.tsc_timestamp  = decoder->tsc_timestamp,
		.timestamp      = decoder->timestamp,
		.have_tma       = decoder->have_tma,
		.fixup_last_mtc = decoder->fixup_last_mtc,
		.from_mtc       = from_mtc,
		.cbr_cyc_to_tsc = 0,
	};

	/*
	 * For now, do not support using TSC packets for at least the reasons:
	 * 1) timing might have stopped
	 * 2) TSC packets within PSB+ can slip against CYC packets
	 */
	if (!from_mtc)
		return;

	intel_pt_pkt_lookahead(decoder, intel_pt_calc_cyc_cb, &data);
}
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
struct intel_pt_params {int mtc_period; int tsc_ctc_ratio_n; int tsc_ctc_ratio_d; int /*<<< orphan*/  max_non_turbo_ratio; int /*<<< orphan*/  period_type; int /*<<< orphan*/  period; int /*<<< orphan*/  flags; int /*<<< orphan*/  branch_enable; int /*<<< orphan*/  return_compression; int /*<<< orphan*/  data; int /*<<< orphan*/  lookahead; int /*<<< orphan*/  pgd_ip; scalar_t__ walk_insn; scalar_t__ get_trace; } ;
struct intel_pt_decoder {int mtc_shift; int ctc_rem_mask; int tsc_ctc_ratio_n; int tsc_ctc_ratio_d; int tsc_ctc_mult; int tsc_slip; int /*<<< orphan*/  max_non_turbo_ratio_fp; int /*<<< orphan*/  max_non_turbo_ratio; int /*<<< orphan*/  period_type; int /*<<< orphan*/  period; int /*<<< orphan*/  flags; int /*<<< orphan*/  branch_enable; int /*<<< orphan*/  return_compression; int /*<<< orphan*/  data; int /*<<< orphan*/  lookahead; int /*<<< orphan*/  pgd_ip; scalar_t__ walk_insn; scalar_t__ get_trace; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_pt_log (char*,int) ; 
 int /*<<< orphan*/  intel_pt_setup_period (struct intel_pt_decoder*) ; 
 struct intel_pt_decoder* zalloc (int) ; 

struct intel_pt_decoder *intel_pt_decoder_new(struct intel_pt_params *params)
{
	struct intel_pt_decoder *decoder;

	if (!params->get_trace || !params->walk_insn)
		return NULL;

	decoder = zalloc(sizeof(struct intel_pt_decoder));
	if (!decoder)
		return NULL;

	decoder->get_trace          = params->get_trace;
	decoder->walk_insn          = params->walk_insn;
	decoder->pgd_ip             = params->pgd_ip;
	decoder->lookahead          = params->lookahead;
	decoder->data               = params->data;
	decoder->return_compression = params->return_compression;
	decoder->branch_enable      = params->branch_enable;

	decoder->flags              = params->flags;

	decoder->period             = params->period;
	decoder->period_type        = params->period_type;

	decoder->max_non_turbo_ratio    = params->max_non_turbo_ratio;
	decoder->max_non_turbo_ratio_fp = params->max_non_turbo_ratio;

	intel_pt_setup_period(decoder);

	decoder->mtc_shift = params->mtc_period;
	decoder->ctc_rem_mask = (1 << decoder->mtc_shift) - 1;

	decoder->tsc_ctc_ratio_n = params->tsc_ctc_ratio_n;
	decoder->tsc_ctc_ratio_d = params->tsc_ctc_ratio_d;

	if (!decoder->tsc_ctc_ratio_n)
		decoder->tsc_ctc_ratio_d = 0;

	if (decoder->tsc_ctc_ratio_d) {
		if (!(decoder->tsc_ctc_ratio_n % decoder->tsc_ctc_ratio_d))
			decoder->tsc_ctc_mult = decoder->tsc_ctc_ratio_n /
						decoder->tsc_ctc_ratio_d;
	}

	/*
	 * A TSC packet can slip past MTC packets so that the timestamp appears
	 * to go backwards. One estimate is that can be up to about 40 CPU
	 * cycles, which is certainly less than 0x1000 TSC ticks, but accept
	 * slippage an order of magnitude more to be on the safe side.
	 */
	decoder->tsc_slip = 0x10000;

	intel_pt_log("timestamp: mtc_shift %u\n", decoder->mtc_shift);
	intel_pt_log("timestamp: tsc_ctc_ratio_n %u\n", decoder->tsc_ctc_ratio_n);
	intel_pt_log("timestamp: tsc_ctc_ratio_d %u\n", decoder->tsc_ctc_ratio_d);
	intel_pt_log("timestamp: tsc_ctc_mult %u\n", decoder->tsc_ctc_mult);
	intel_pt_log("timestamp: tsc_slip %#x\n", decoder->tsc_slip);

	return decoder;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct intel_pt_insn {scalar_t__ branch; scalar_t__ length; scalar_t__ op; scalar_t__ rel; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {scalar_t__ from_ip; scalar_t__ to_ip; scalar_t__ insn_op; scalar_t__ insn_len; int flags; int /*<<< orphan*/  insn; int /*<<< orphan*/  type; } ;
struct intel_pt_decoder {int mtc_insn; int (* walk_insn ) (struct intel_pt_insn*,scalar_t__*,scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ;scalar_t__ ip; scalar_t__ stuck_ip; int stuck_ip_prd; int stuck_ip_cnt; int tx_flags; TYPE_1__ state; scalar_t__ no_progress; int /*<<< orphan*/  pkt_state; int /*<<< orphan*/  stack; int /*<<< orphan*/  ret_addr; int /*<<< orphan*/  period_insn_cnt; int /*<<< orphan*/  sample_insn_cnt; int /*<<< orphan*/  timestamp_insn_cnt; int /*<<< orphan*/  tot_insn_cnt; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EILSEQ ; 
 int ELOOP ; 
 int ENOENT ; 
 int ENOLINK ; 
 scalar_t__ INTEL_PT_BR_NO_BRANCH ; 
 scalar_t__ INTEL_PT_BR_UNCONDITIONAL ; 
 int /*<<< orphan*/  INTEL_PT_INSN_BUF_SZ ; 
 int /*<<< orphan*/  INTEL_PT_INSTRUCTION ; 
 int INTEL_PT_IN_TX ; 
 int INTEL_PT_MAX_LOOPS ; 
 scalar_t__ INTEL_PT_OP_CALL ; 
 scalar_t__ INTEL_PT_OP_RET ; 
 int INTEL_PT_RETURN ; 
 int /*<<< orphan*/  INTEL_PT_STATE_ERR2 ; 
 int /*<<< orphan*/  INTEL_PT_STATE_ERR_RESYNC ; 
 int /*<<< orphan*/  intel_pt_log_at (char*,scalar_t__) ; 
 scalar_t__ intel_pt_next_sample (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_pop (int /*<<< orphan*/ *) ; 
 int intel_pt_push (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  intel_pt_sample_insn (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct intel_pt_insn*,scalar_t__*,scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pt_walk_insn(struct intel_pt_decoder *decoder,
			      struct intel_pt_insn *intel_pt_insn, uint64_t ip)
{
	uint64_t max_insn_cnt, insn_cnt = 0;
	int err;

	if (!decoder->mtc_insn)
		decoder->mtc_insn = true;

	max_insn_cnt = intel_pt_next_sample(decoder);

	err = decoder->walk_insn(intel_pt_insn, &insn_cnt, &decoder->ip, ip,
				 max_insn_cnt, decoder->data);

	decoder->tot_insn_cnt += insn_cnt;
	decoder->timestamp_insn_cnt += insn_cnt;
	decoder->sample_insn_cnt += insn_cnt;
	decoder->period_insn_cnt += insn_cnt;

	if (err) {
		decoder->no_progress = 0;
		decoder->pkt_state = INTEL_PT_STATE_ERR2;
		intel_pt_log_at("ERROR: Failed to get instruction",
				decoder->ip);
		if (err == -ENOENT)
			return -ENOLINK;
		return -EILSEQ;
	}

	if (ip && decoder->ip == ip) {
		err = -EAGAIN;
		goto out;
	}

	if (max_insn_cnt && insn_cnt >= max_insn_cnt)
		intel_pt_sample_insn(decoder);

	if (intel_pt_insn->branch == INTEL_PT_BR_NO_BRANCH) {
		decoder->state.type = INTEL_PT_INSTRUCTION;
		decoder->state.from_ip = decoder->ip;
		decoder->state.to_ip = 0;
		decoder->ip += intel_pt_insn->length;
		err = INTEL_PT_RETURN;
		goto out;
	}

	if (intel_pt_insn->op == INTEL_PT_OP_CALL) {
		/* Zero-length calls are excluded */
		if (intel_pt_insn->branch != INTEL_PT_BR_UNCONDITIONAL ||
		    intel_pt_insn->rel) {
			err = intel_pt_push(&decoder->stack, decoder->ip +
					    intel_pt_insn->length);
			if (err)
				goto out;
		}
	} else if (intel_pt_insn->op == INTEL_PT_OP_RET) {
		decoder->ret_addr = intel_pt_pop(&decoder->stack);
	}

	if (intel_pt_insn->branch == INTEL_PT_BR_UNCONDITIONAL) {
		int cnt = decoder->no_progress++;

		decoder->state.from_ip = decoder->ip;
		decoder->ip += intel_pt_insn->length +
				intel_pt_insn->rel;
		decoder->state.to_ip = decoder->ip;
		err = INTEL_PT_RETURN;

		/*
		 * Check for being stuck in a loop.  This can happen if a
		 * decoder error results in the decoder erroneously setting the
		 * ip to an address that is itself in an infinite loop that
		 * consumes no packets.  When that happens, there must be an
		 * unconditional branch.
		 */
		if (cnt) {
			if (cnt == 1) {
				decoder->stuck_ip = decoder->state.to_ip;
				decoder->stuck_ip_prd = 1;
				decoder->stuck_ip_cnt = 1;
			} else if (cnt > INTEL_PT_MAX_LOOPS ||
				   decoder->state.to_ip == decoder->stuck_ip) {
				intel_pt_log_at("ERROR: Never-ending loop",
						decoder->state.to_ip);
				decoder->pkt_state = INTEL_PT_STATE_ERR_RESYNC;
				err = -ELOOP;
				goto out;
			} else if (!--decoder->stuck_ip_cnt) {
				decoder->stuck_ip_prd += 1;
				decoder->stuck_ip_cnt = decoder->stuck_ip_prd;
				decoder->stuck_ip = decoder->state.to_ip;
			}
		}
		goto out_no_progress;
	}
out:
	decoder->no_progress = 0;
out_no_progress:
	decoder->state.insn_op = intel_pt_insn->op;
	decoder->state.insn_len = intel_pt_insn->length;
	memcpy(decoder->state.insn, intel_pt_insn->buf,
	       INTEL_PT_INSN_BUF_SZ);

	if (decoder->tx_flags & INTEL_PT_IN_TX)
		decoder->state.flags |= INTEL_PT_IN_TX;

	return err;
}
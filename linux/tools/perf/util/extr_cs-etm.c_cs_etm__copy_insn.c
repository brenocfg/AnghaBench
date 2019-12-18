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
typedef  int /*<<< orphan*/  u64 ;
struct perf_sample {int insn_len; scalar_t__ insn; int /*<<< orphan*/  ip; } ;
struct cs_etm_queue {int dummy; } ;
struct cs_etm_packet {scalar_t__ sample_type; scalar_t__ isa; } ;

/* Variables and functions */
 scalar_t__ CS_ETM_DISCONTINUITY ; 
 scalar_t__ CS_ETM_ISA_T32 ; 
 int /*<<< orphan*/  cs_etm__mem_access (struct cs_etm_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,void*) ; 
 int cs_etm__t32_instr_size (struct cs_etm_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs_etm__copy_insn(struct cs_etm_queue *etmq,
			      u64 trace_chan_id,
			      const struct cs_etm_packet *packet,
			      struct perf_sample *sample)
{
	/*
	 * It's pointless to read instructions for the CS_ETM_DISCONTINUITY
	 * packet, so directly bail out with 'insn_len' = 0.
	 */
	if (packet->sample_type == CS_ETM_DISCONTINUITY) {
		sample->insn_len = 0;
		return;
	}

	/*
	 * T32 instruction size might be 32-bit or 16-bit, decide by calling
	 * cs_etm__t32_instr_size().
	 */
	if (packet->isa == CS_ETM_ISA_T32)
		sample->insn_len = cs_etm__t32_instr_size(etmq, trace_chan_id,
							  sample->ip);
	/* Otherwise, A64 and A32 instruction size are always 32-bit. */
	else
		sample->insn_len = 4;

	cs_etm__mem_access(etmq, trace_chan_id, sample->ip,
			   sample->insn_len, (void *)sample->insn);
}
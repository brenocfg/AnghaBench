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
struct intel_pt_decoder {int overflow; int /*<<< orphan*/  pkt_state; scalar_t__ timestamp_insn_cnt; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int /*<<< orphan*/  INTEL_PT_STATE_ERR_RESYNC ; 
 int /*<<< orphan*/  intel_pt_clear_tx_flags (struct intel_pt_decoder*) ; 
 int /*<<< orphan*/  intel_pt_log (char*) ; 

__attribute__((used)) static int intel_pt_overflow(struct intel_pt_decoder *decoder)
{
	intel_pt_log("ERROR: Buffer overflow\n");
	intel_pt_clear_tx_flags(decoder);
	decoder->timestamp_insn_cnt = 0;
	decoder->pkt_state = INTEL_PT_STATE_ERR_RESYNC;
	decoder->overflow = true;
	return -EOVERFLOW;
}
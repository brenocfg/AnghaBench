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
typedef  unsigned long long uint64_t ;
struct TYPE_2__ {int payload; } ;
struct intel_pt_decoder {int have_tma; int ref_timestamp; unsigned long long tsc_timestamp; unsigned long long timestamp; unsigned long long tsc_slip; scalar_t__ last_packet_type; unsigned long long cyc_ref_timestamp; int have_calc_cyc_to_tsc; scalar_t__ cycle_cnt; scalar_t__ timestamp_insn_cnt; TYPE_1__ packet; } ;

/* Variables and functions */
 scalar_t__ INTEL_PT_CYC ; 
 int /*<<< orphan*/  intel_pt_calc_cyc_to_tsc (struct intel_pt_decoder*,int) ; 
 int /*<<< orphan*/  intel_pt_log_to (char*,unsigned long long) ; 

__attribute__((used)) static void intel_pt_calc_tsc_timestamp(struct intel_pt_decoder *decoder)
{
	uint64_t timestamp;

	decoder->have_tma = false;

	if (decoder->ref_timestamp) {
		timestamp = decoder->packet.payload |
			    (decoder->ref_timestamp & (0xffULL << 56));
		if (timestamp < decoder->ref_timestamp) {
			if (decoder->ref_timestamp - timestamp > (1ULL << 55))
				timestamp += (1ULL << 56);
		} else {
			if (timestamp - decoder->ref_timestamp > (1ULL << 55))
				timestamp -= (1ULL << 56);
		}
		decoder->tsc_timestamp = timestamp;
		decoder->timestamp = timestamp;
		decoder->ref_timestamp = 0;
		decoder->timestamp_insn_cnt = 0;
	} else if (decoder->timestamp) {
		timestamp = decoder->packet.payload |
			    (decoder->timestamp & (0xffULL << 56));
		decoder->tsc_timestamp = timestamp;
		if (timestamp < decoder->timestamp &&
		    decoder->timestamp - timestamp < decoder->tsc_slip) {
			intel_pt_log_to("Suppressing backwards timestamp",
					timestamp);
			timestamp = decoder->timestamp;
		}
		if (timestamp < decoder->timestamp) {
			intel_pt_log_to("Wraparound timestamp", timestamp);
			timestamp += (1ULL << 56);
			decoder->tsc_timestamp = timestamp;
		}
		decoder->timestamp = timestamp;
		decoder->timestamp_insn_cnt = 0;
	}

	if (decoder->last_packet_type == INTEL_PT_CYC) {
		decoder->cyc_ref_timestamp = decoder->timestamp;
		decoder->cycle_cnt = 0;
		decoder->have_calc_cyc_to_tsc = false;
		intel_pt_calc_cyc_to_tsc(decoder, false);
	}

	intel_pt_log_to("Setting timestamp", decoder->timestamp);
}
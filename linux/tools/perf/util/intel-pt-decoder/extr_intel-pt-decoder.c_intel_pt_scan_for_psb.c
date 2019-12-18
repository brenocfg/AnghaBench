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
struct intel_pt_decoder {int buf; unsigned char* pkt_step; scalar_t__ len; int /*<<< orphan*/  pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_PSB_LEN ; 
 int /*<<< orphan*/  INTEL_PT_PSB_STR ; 
 int intel_pt_get_next_data (struct intel_pt_decoder*,int) ; 
 int intel_pt_get_next_packet (struct intel_pt_decoder*) ; 
 int intel_pt_get_split_psb (struct intel_pt_decoder*,int) ; 
 int /*<<< orphan*/  intel_pt_log (char*) ; 
 int intel_pt_part_psb (struct intel_pt_decoder*) ; 
 unsigned char* memmem (int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_pt_scan_for_psb(struct intel_pt_decoder *decoder)
{
	unsigned char *next;
	int ret;

	intel_pt_log("Scanning for PSB\n");
	while (1) {
		if (!decoder->len) {
			ret = intel_pt_get_next_data(decoder, false);
			if (ret)
				return ret;
		}

		next = memmem(decoder->buf, decoder->len, INTEL_PT_PSB_STR,
			      INTEL_PT_PSB_LEN);
		if (!next) {
			int part_psb;

			part_psb = intel_pt_part_psb(decoder);
			if (part_psb) {
				ret = intel_pt_get_split_psb(decoder, part_psb);
				if (ret)
					return ret;
			} else {
				decoder->pos += decoder->len;
				decoder->len = 0;
			}
			continue;
		}

		decoder->pkt_step = next - decoder->buf;
		return intel_pt_get_next_packet(decoder);
	}
}
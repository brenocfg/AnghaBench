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
typedef  int /*<<< orphan*/  uint64_t ;
struct intel_pt_pkt {scalar_t__ type; int /*<<< orphan*/  payload; } ;

/* Variables and functions */
 scalar_t__ INTEL_PT_PSBEND ; 
 scalar_t__ INTEL_PT_TSC ; 
 int intel_pt_get_packet (unsigned char*,size_t,struct intel_pt_pkt*) ; 

__attribute__((used)) static bool intel_pt_next_tsc(unsigned char *buf, size_t len, uint64_t *tsc,
			      size_t *rem)
{
	struct intel_pt_pkt packet;
	int ret;

	while (len) {
		ret = intel_pt_get_packet(buf, len, &packet);
		if (ret <= 0)
			return false;
		if (packet.type == INTEL_PT_TSC) {
			*tsc = packet.payload;
			*rem = len;
			return true;
		}
		if (packet.type == INTEL_PT_PSBEND)
			return false;
		buf += ret;
		len -= ret;
	}
	return false;
}
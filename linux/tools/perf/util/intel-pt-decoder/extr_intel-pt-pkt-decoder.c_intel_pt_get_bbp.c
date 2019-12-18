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
struct intel_pt_pkt {unsigned char count; unsigned char payload; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_BBP ; 
 int INTEL_PT_NEED_MORE_BYTES ; 

__attribute__((used)) static int intel_pt_get_bbp(const unsigned char *buf, size_t len,
			    struct intel_pt_pkt *packet)
{
	if (len < 3)
		return INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_BBP;
	packet->count = buf[2] >> 7;
	packet->payload = buf[2] & 0x1f;
	return 3;
}
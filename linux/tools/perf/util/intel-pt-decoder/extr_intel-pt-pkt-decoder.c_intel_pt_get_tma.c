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
struct intel_pt_pkt {unsigned char payload; unsigned char count; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 unsigned char const BIT (int /*<<< orphan*/ ) ; 
 int INTEL_PT_NEED_MORE_BYTES ; 
 int /*<<< orphan*/  INTEL_PT_TMA ; 

__attribute__((used)) static int intel_pt_get_tma(const unsigned char *buf, size_t len,
			    struct intel_pt_pkt *packet)
{
	if (len < 7)
		return INTEL_PT_NEED_MORE_BYTES;

	packet->type = INTEL_PT_TMA;
	packet->payload = buf[2] | (buf[3] << 8);
	packet->count = buf[5] | ((buf[6] & BIT(0)) << 8);
	return 7;
}
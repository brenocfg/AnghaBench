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
struct intel_pt_pkt {unsigned char payload; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_PT_MTC ; 
 int INTEL_PT_NEED_MORE_BYTES ; 

__attribute__((used)) static int intel_pt_get_mtc(const unsigned char *buf, size_t len,
			    struct intel_pt_pkt *packet)
{
	if (len < 2)
		return INTEL_PT_NEED_MORE_BYTES;
	packet->type = INTEL_PT_MTC;
	packet->payload = buf[1];
	return 2;
}
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
typedef  int uint64_t ;
struct intel_pt_pkt {int payload; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int INTEL_PT_NEED_MORE_BYTES ; 
 int /*<<< orphan*/  INTEL_PT_PIP ; 
 int NR_FLAG ; 
 int /*<<< orphan*/  memcpy_le64 (int*,unsigned char const*,int) ; 

__attribute__((used)) static int intel_pt_get_pip(const unsigned char *buf, size_t len,
			    struct intel_pt_pkt *packet)
{
	uint64_t payload = 0;

	if (len < 8)
		return INTEL_PT_NEED_MORE_BYTES;

	packet->type = INTEL_PT_PIP;
	memcpy_le64(&payload, buf + 2, 6);
	packet->payload = payload >> 1;
	if (payload & 1)
		packet->payload |= NR_FLAG;

	return 8;
}
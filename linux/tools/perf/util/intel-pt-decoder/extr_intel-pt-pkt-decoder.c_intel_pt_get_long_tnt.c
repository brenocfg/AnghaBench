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
struct intel_pt_pkt {int count; int payload; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int BIT63 ; 
 int INTEL_PT_NEED_MORE_BYTES ; 
 int /*<<< orphan*/  INTEL_PT_TNT ; 
 int le64_to_cpu (int) ; 

__attribute__((used)) static int intel_pt_get_long_tnt(const unsigned char *buf, size_t len,
				 struct intel_pt_pkt *packet)
{
	uint64_t payload;
	int count;

	if (len < 8)
		return INTEL_PT_NEED_MORE_BYTES;

	payload = le64_to_cpu(*(uint64_t *)buf);

	for (count = 47; count; count--) {
		if (payload & BIT63)
			break;
		payload <<= 1;
	}

	packet->type = INTEL_PT_TNT;
	packet->count = count;
	packet->payload = payload << 1;
	return 8;
}
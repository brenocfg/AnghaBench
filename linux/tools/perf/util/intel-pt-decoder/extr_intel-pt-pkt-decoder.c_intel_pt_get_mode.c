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
struct intel_pt_pkt {int payload; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int INTEL_PT_BAD_PACKET ; 
 int /*<<< orphan*/  INTEL_PT_MODE_EXEC ; 
 int /*<<< orphan*/  INTEL_PT_MODE_TSX ; 
 int INTEL_PT_NEED_MORE_BYTES ; 

__attribute__((used)) static int intel_pt_get_mode(const unsigned char *buf, size_t len,
			     struct intel_pt_pkt *packet)
{
	if (len < 2)
		return INTEL_PT_NEED_MORE_BYTES;

	switch (buf[1] >> 5) {
	case 0:
		packet->type = INTEL_PT_MODE_EXEC;
		switch (buf[1] & 3) {
		case 0:
			packet->payload = 16;
			break;
		case 1:
			packet->payload = 64;
			break;
		case 2:
			packet->payload = 32;
			break;
		default:
			return INTEL_PT_BAD_PACKET;
		}
		break;
	case 1:
		packet->type = INTEL_PT_MODE_TSX;
		if ((buf[1] & 3) == 3)
			return INTEL_PT_BAD_PACKET;
		packet->payload = buf[1] & 3;
		break;
	default:
		return INTEL_PT_BAD_PACKET;
	}

	return 2;
}
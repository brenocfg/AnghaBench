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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct intel_pt_pkt {unsigned int count; int type; int /*<<< orphan*/  payload; } ;
typedef  enum intel_pt_pkt_type { ____Placeholder_intel_pt_pkt_type } intel_pt_pkt_type ;

/* Variables and functions */
 int INTEL_PT_BAD_PACKET ; 
 int INTEL_PT_NEED_MORE_BYTES ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy_le64 (int /*<<< orphan*/ *,unsigned char const*,int) ; 

__attribute__((used)) static int intel_pt_get_ip(enum intel_pt_pkt_type type, unsigned int byte,
			   const unsigned char *buf, size_t len,
			   struct intel_pt_pkt *packet)
{
	int ip_len;

	packet->count = byte >> 5;

	switch (packet->count) {
	case 0:
		ip_len = 0;
		break;
	case 1:
		if (len < 3)
			return INTEL_PT_NEED_MORE_BYTES;
		ip_len = 2;
		packet->payload = le16_to_cpu(*(uint16_t *)(buf + 1));
		break;
	case 2:
		if (len < 5)
			return INTEL_PT_NEED_MORE_BYTES;
		ip_len = 4;
		packet->payload = le32_to_cpu(*(uint32_t *)(buf + 1));
		break;
	case 3:
	case 4:
		if (len < 7)
			return INTEL_PT_NEED_MORE_BYTES;
		ip_len = 6;
		memcpy_le64(&packet->payload, buf + 1, 6);
		break;
	case 6:
		if (len < 9)
			return INTEL_PT_NEED_MORE_BYTES;
		ip_len = 8;
		packet->payload = le64_to_cpu(*(uint64_t *)(buf + 1));
		break;
	default:
		return INTEL_PT_BAD_PACKET;
	}

	packet->type = type;

	return ip_len + 1;
}
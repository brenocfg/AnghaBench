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
struct arm_spe_pkt {unsigned char index; int /*<<< orphan*/  payload; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_SPE_ADDRESS ; 
 int ARM_SPE_NEED_MORE_BYTES ; 
 int /*<<< orphan*/  memcpy_le64 (int /*<<< orphan*/ *,unsigned char const*,int) ; 

__attribute__((used)) static int arm_spe_get_addr(const unsigned char *buf, size_t len,
			    const unsigned char ext_hdr, struct arm_spe_pkt *packet)
{
	if (len < 8)
		return ARM_SPE_NEED_MORE_BYTES;

	packet->type = ARM_SPE_ADDRESS;
	if (ext_hdr)
		packet->index = ((buf[0] & 0x3) << 3) | (buf[1] & 0x7);
	else
		packet->index = buf[0] & 0x7;

	memcpy_le64(&packet->payload, buf + 1, 8);

	return 1 + ext_hdr + 8;
}
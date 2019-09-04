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
typedef  int u32 ;
struct smp_req {void* len_ip_ir; void* device_id; int /*<<< orphan*/  tag; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int SMP_DIRECT ; 
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static void build_smp_cmd(u32 deviceID, __le32 hTag,
			struct smp_req *psmp_cmd, int mode, int length)
{
	psmp_cmd->tag = hTag;
	psmp_cmd->device_id = cpu_to_le32(deviceID);
	if (mode == SMP_DIRECT) {
		length = length - 4; /* subtract crc */
		psmp_cmd->len_ip_ir = cpu_to_le32(length << 16);
	} else {
		psmp_cmd->len_ip_ir = cpu_to_le32(1|(1 << 1));
	}
}
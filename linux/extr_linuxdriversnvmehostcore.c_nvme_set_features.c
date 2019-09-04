#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
union nvme_result {int /*<<< orphan*/  u32; } ;
typedef  int /*<<< orphan*/  u32 ;
struct nvme_ctrl {int /*<<< orphan*/  admin_q; } ;
struct TYPE_2__ {void* dword11; void* fid; int /*<<< orphan*/  opcode; } ;
struct nvme_command {TYPE_1__ features; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_QID_ANY ; 
 int __nvme_submit_sync_cmd (int /*<<< orphan*/ ,struct nvme_command*,union nvme_result*,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvme_admin_set_features ; 

__attribute__((used)) static int nvme_set_features(struct nvme_ctrl *dev, unsigned fid, unsigned dword11,
		      void *buffer, size_t buflen, u32 *result)
{
	struct nvme_command c;
	union nvme_result res;
	int ret;

	memset(&c, 0, sizeof(c));
	c.features.opcode = nvme_admin_set_features;
	c.features.fid = cpu_to_le32(fid);
	c.features.dword11 = cpu_to_le32(dword11);

	ret = __nvme_submit_sync_cmd(dev->admin_q, &c, &res,
			buffer, buflen, 0, NVME_QID_ANY, 0, 0);
	if (ret >= 0 && result)
		*result = le32_to_cpu(res.u32);
	return ret;
}
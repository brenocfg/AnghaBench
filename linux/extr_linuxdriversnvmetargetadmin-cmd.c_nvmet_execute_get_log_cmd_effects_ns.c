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
typedef  int /*<<< orphan*/  u16 ;
struct nvmet_req {int dummy; } ;
struct nvme_effects_log {void** iocs; void** acs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVME_SC_INTERNAL ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  kfree (struct nvme_effects_log*) ; 
 struct nvme_effects_log* kzalloc (int,int /*<<< orphan*/ ) ; 
 size_t nvme_admin_abort_cmd ; 
 size_t nvme_admin_async_event ; 
 size_t nvme_admin_get_features ; 
 size_t nvme_admin_get_log_page ; 
 size_t nvme_admin_identify ; 
 size_t nvme_admin_keep_alive ; 
 size_t nvme_admin_set_features ; 
 size_t nvme_cmd_dsm ; 
 size_t nvme_cmd_flush ; 
 size_t nvme_cmd_read ; 
 size_t nvme_cmd_write ; 
 size_t nvme_cmd_write_zeroes ; 
 int /*<<< orphan*/  nvmet_copy_to_sgl (struct nvmet_req*,int /*<<< orphan*/ ,struct nvme_effects_log*,int) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvmet_execute_get_log_cmd_effects_ns(struct nvmet_req *req)
{
	u16 status = NVME_SC_INTERNAL;
	struct nvme_effects_log *log;

	log = kzalloc(sizeof(*log), GFP_KERNEL);
	if (!log)
		goto out;

	log->acs[nvme_admin_get_log_page]	= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_identify]		= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_abort_cmd]		= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_set_features]	= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_get_features]	= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_async_event]	= cpu_to_le32(1 << 0);
	log->acs[nvme_admin_keep_alive]		= cpu_to_le32(1 << 0);

	log->iocs[nvme_cmd_read]		= cpu_to_le32(1 << 0);
	log->iocs[nvme_cmd_write]		= cpu_to_le32(1 << 0);
	log->iocs[nvme_cmd_flush]		= cpu_to_le32(1 << 0);
	log->iocs[nvme_cmd_dsm]			= cpu_to_le32(1 << 0);
	log->iocs[nvme_cmd_write_zeroes]	= cpu_to_le32(1 << 0);

	status = nvmet_copy_to_sgl(req, 0, log, sizeof(*log));

	kfree(log);
out:
	nvmet_req_complete(req, status);
}
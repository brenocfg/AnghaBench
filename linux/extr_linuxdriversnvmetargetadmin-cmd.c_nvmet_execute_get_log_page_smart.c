#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct nvmet_req {int data_len; TYPE_2__* cmd; } ;
struct nvme_smart_log {int dummy; } ;
struct TYPE_3__ {scalar_t__ nsid; } ;
struct TYPE_4__ {TYPE_1__ get_log_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVME_NSID_ALL ; 
 scalar_t__ NVME_SC_INTERNAL ; 
 scalar_t__ cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nvme_smart_log*) ; 
 struct nvme_smart_log* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nvmet_copy_to_sgl (struct nvmet_req*,int /*<<< orphan*/ ,struct nvme_smart_log*,int) ; 
 scalar_t__ nvmet_get_smart_log_all (struct nvmet_req*,struct nvme_smart_log*) ; 
 scalar_t__ nvmet_get_smart_log_nsid (struct nvmet_req*,struct nvme_smart_log*) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,scalar_t__) ; 

__attribute__((used)) static void nvmet_execute_get_log_page_smart(struct nvmet_req *req)
{
	struct nvme_smart_log *log;
	u16 status = NVME_SC_INTERNAL;

	if (req->data_len != sizeof(*log))
		goto out;

	log = kzalloc(sizeof(*log), GFP_KERNEL);
	if (!log)
		goto out;

	if (req->cmd->get_log_page.nsid == cpu_to_le32(NVME_NSID_ALL))
		status = nvmet_get_smart_log_all(req, log);
	else
		status = nvmet_get_smart_log_nsid(req, log);
	if (status)
		goto out_free_log;

	status = nvmet_copy_to_sgl(req, 0, log, sizeof(*log));
out_free_log:
	kfree(log);
out:
	nvmet_req_complete(req, status);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct nvmet_req {int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg; TYPE_3__* cmd; TYPE_1__* sq; } ;
struct nvmet_ns {int /*<<< orphan*/ **** nguid; int /*<<< orphan*/ **** uuid; } ;
typedef  scalar_t__ off_t ;
struct TYPE_5__ {int /*<<< orphan*/  nsid; } ;
struct TYPE_6__ {TYPE_2__ identify; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 scalar_t__ NVME_IDENTIFY_DATA_SIZE ; 
 int /*<<< orphan*/  NVME_NIDT_NGUID ; 
 int /*<<< orphan*/  NVME_NIDT_NGUID_LEN ; 
 int /*<<< orphan*/  NVME_NIDT_UUID ; 
 int /*<<< orphan*/  NVME_NIDT_UUID_LEN ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INTERNAL ; 
 int NVME_SC_INVALID_NS ; 
 scalar_t__ memchr_inv (int /*<<< orphan*/ ***,int /*<<< orphan*/ ,int) ; 
 int nvmet_copy_ns_identifier (struct nvmet_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ****,scalar_t__*) ; 
 struct nvmet_ns* nvmet_find_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_put_namespace (struct nvmet_ns*) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 
 scalar_t__ sg_zero_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void nvmet_execute_identify_desclist(struct nvmet_req *req)
{
	struct nvmet_ns *ns;
	u16 status = 0;
	off_t off = 0;

	ns = nvmet_find_namespace(req->sq->ctrl, req->cmd->identify.nsid);
	if (!ns) {
		status = NVME_SC_INVALID_NS | NVME_SC_DNR;
		goto out;
	}

	if (memchr_inv(&ns->uuid, 0, sizeof(ns->uuid))) {
		status = nvmet_copy_ns_identifier(req, NVME_NIDT_UUID,
						  NVME_NIDT_UUID_LEN,
						  &ns->uuid, &off);
		if (status)
			goto out_put_ns;
	}
	if (memchr_inv(ns->nguid, 0, sizeof(ns->nguid))) {
		status = nvmet_copy_ns_identifier(req, NVME_NIDT_NGUID,
						  NVME_NIDT_NGUID_LEN,
						  &ns->nguid, &off);
		if (status)
			goto out_put_ns;
	}

	if (sg_zero_buffer(req->sg, req->sg_cnt, NVME_IDENTIFY_DATA_SIZE - off,
			off) != NVME_IDENTIFY_DATA_SIZE - off)
		status = NVME_SC_INTERNAL | NVME_SC_DNR;
out_put_ns:
	nvmet_put_namespace(ns);
out:
	nvmet_req_complete(req, status);
}
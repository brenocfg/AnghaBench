#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct nvmet_req {TYPE_4__* port; TYPE_3__* cmd; TYPE_1__* sq; } ;
struct nvmet_ns {int size; int blksize_shift; size_t anagrpid; scalar_t__ readonly; int /*<<< orphan*/  nguid; } ;
struct nvme_id_ns {int nmic; int nsattr; TYPE_5__* lbaf; int /*<<< orphan*/  nguid; int /*<<< orphan*/  anagrpid; scalar_t__ flbas; scalar_t__ nlbaf; int /*<<< orphan*/  nsze; int /*<<< orphan*/  nuse; int /*<<< orphan*/  ncap; } ;
struct TYPE_10__ {int ds; } ;
struct TYPE_9__ {int* ana_state; } ;
struct TYPE_7__ {int /*<<< orphan*/  nsid; } ;
struct TYPE_8__ {TYPE_2__ identify; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  NVME_ANA_INACCESSIBLE 129 
#define  NVME_ANA_PERSISTENT_LOSS 128 
 scalar_t__ NVME_NSID_ALL ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INTERNAL ; 
 int NVME_SC_INVALID_NS ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  kfree (struct nvme_id_ns*) ; 
 struct nvme_id_ns* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int nvmet_copy_to_sgl (struct nvmet_req*,int /*<<< orphan*/ ,struct nvme_id_ns*,int) ; 
 struct nvmet_ns* nvmet_find_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_put_namespace (struct nvmet_ns*) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,int) ; 

__attribute__((used)) static void nvmet_execute_identify_ns(struct nvmet_req *req)
{
	struct nvmet_ns *ns;
	struct nvme_id_ns *id;
	u16 status = 0;

	if (le32_to_cpu(req->cmd->identify.nsid) == NVME_NSID_ALL) {
		status = NVME_SC_INVALID_NS | NVME_SC_DNR;
		goto out;
	}

	id = kzalloc(sizeof(*id), GFP_KERNEL);
	if (!id) {
		status = NVME_SC_INTERNAL;
		goto out;
	}

	/* return an all zeroed buffer if we can't find an active namespace */
	ns = nvmet_find_namespace(req->sq->ctrl, req->cmd->identify.nsid);
	if (!ns)
		goto done;

	/*
	 * nuse = ncap = nsze isn't always true, but we have no way to find
	 * that out from the underlying device.
	 */
	id->ncap = id->nsze = cpu_to_le64(ns->size >> ns->blksize_shift);
	switch (req->port->ana_state[ns->anagrpid]) {
	case NVME_ANA_INACCESSIBLE:
	case NVME_ANA_PERSISTENT_LOSS:
		break;
	default:
		id->nuse = id->nsze;
		break;
        }

	/*
	 * We just provide a single LBA format that matches what the
	 * underlying device reports.
	 */
	id->nlbaf = 0;
	id->flbas = 0;

	/*
	 * Our namespace might always be shared.  Not just with other
	 * controllers, but also with any other user of the block device.
	 */
	id->nmic = (1 << 0);
	id->anagrpid = cpu_to_le32(ns->anagrpid);

	memcpy(&id->nguid, &ns->nguid, sizeof(id->nguid));

	id->lbaf[0].ds = ns->blksize_shift;

	if (ns->readonly)
		id->nsattr |= (1 << 0);
	nvmet_put_namespace(ns);
done:
	status = nvmet_copy_to_sgl(req, 0, id, sizeof(*id));
	kfree(id);
out:
	nvmet_req_complete(req, status);
}
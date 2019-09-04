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
typedef  int /*<<< orphan*/  u32 ;
struct nvmet_fc_tgtport {int dummy; } ;
struct nvmet_fc_target_port {int dummy; } ;
struct nvmet_fc_ls_iod {int /*<<< orphan*/  work; int /*<<< orphan*/  rqstdatalen; int /*<<< orphan*/  rqstbuf; int /*<<< orphan*/ * fcpreq; struct nvmefc_tgt_ls_req* lsreq; } ;
struct nvmefc_tgt_ls_req {int dummy; } ;

/* Variables and functions */
 int E2BIG ; 
 int ENOENT ; 
 int ESHUTDOWN ; 
 int /*<<< orphan*/  NVME_FC_MAX_LS_BUFFER_SIZE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 struct nvmet_fc_ls_iod* nvmet_fc_alloc_ls_iod (struct nvmet_fc_tgtport*) ; 
 int /*<<< orphan*/  nvmet_fc_tgtport_get (struct nvmet_fc_tgtport*) ; 
 int /*<<< orphan*/  nvmet_fc_tgtport_put (struct nvmet_fc_tgtport*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct nvmet_fc_tgtport* targetport_to_tgtport (struct nvmet_fc_target_port*) ; 

int
nvmet_fc_rcv_ls_req(struct nvmet_fc_target_port *target_port,
			struct nvmefc_tgt_ls_req *lsreq,
			void *lsreqbuf, u32 lsreqbuf_len)
{
	struct nvmet_fc_tgtport *tgtport = targetport_to_tgtport(target_port);
	struct nvmet_fc_ls_iod *iod;

	if (lsreqbuf_len > NVME_FC_MAX_LS_BUFFER_SIZE)
		return -E2BIG;

	if (!nvmet_fc_tgtport_get(tgtport))
		return -ESHUTDOWN;

	iod = nvmet_fc_alloc_ls_iod(tgtport);
	if (!iod) {
		nvmet_fc_tgtport_put(tgtport);
		return -ENOENT;
	}

	iod->lsreq = lsreq;
	iod->fcpreq = NULL;
	memcpy(iod->rqstbuf, lsreqbuf, lsreqbuf_len);
	iod->rqstdatalen = lsreqbuf_len;

	schedule_work(&iod->work);

	return 0;
}
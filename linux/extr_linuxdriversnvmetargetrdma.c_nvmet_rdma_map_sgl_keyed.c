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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct rdma_cm_id {int /*<<< orphan*/  port_num; int /*<<< orphan*/  qp; } ;
struct TYPE_4__ {int /*<<< orphan*/  transfer_len; int /*<<< orphan*/  sg_cnt; int /*<<< orphan*/  sg; } ;
struct nvmet_rdma_rsp {int n_rdma; int /*<<< orphan*/  flags; scalar_t__ invalidate_rkey; TYPE_2__ req; int /*<<< orphan*/  rw; TYPE_1__* queue; } ;
struct nvme_keyed_sgl_desc {int /*<<< orphan*/  key; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {struct rdma_cm_id* cm_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NVMET_RDMA_REQ_INVALIDATE_RKEY ; 
 int /*<<< orphan*/  NVME_SC_INTERNAL ; 
 scalar_t__ get_unaligned_le24 (int /*<<< orphan*/ ) ; 
 scalar_t__ get_unaligned_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_data_dir (TYPE_2__*) ; 
 int rdma_rw_ctx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sgl_alloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u16 nvmet_rdma_map_sgl_keyed(struct nvmet_rdma_rsp *rsp,
		struct nvme_keyed_sgl_desc *sgl, bool invalidate)
{
	struct rdma_cm_id *cm_id = rsp->queue->cm_id;
	u64 addr = le64_to_cpu(sgl->addr);
	u32 len = get_unaligned_le24(sgl->length);
	u32 key = get_unaligned_le32(sgl->key);
	int ret;

	/* no data command? */
	if (!len)
		return 0;

	rsp->req.sg = sgl_alloc(len, GFP_KERNEL, &rsp->req.sg_cnt);
	if (!rsp->req.sg)
		return NVME_SC_INTERNAL;

	ret = rdma_rw_ctx_init(&rsp->rw, cm_id->qp, cm_id->port_num,
			rsp->req.sg, rsp->req.sg_cnt, 0, addr, key,
			nvmet_data_dir(&rsp->req));
	if (ret < 0)
		return NVME_SC_INTERNAL;
	rsp->req.transfer_len += len;
	rsp->n_rdma += ret;

	if (invalidate) {
		rsp->invalidate_rkey = key;
		rsp->flags |= NVMET_RDMA_REQ_INVALIDATE_RKEY;
	}

	return 0;
}
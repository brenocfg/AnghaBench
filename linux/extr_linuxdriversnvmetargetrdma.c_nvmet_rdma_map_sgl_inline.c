#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_11__ {int /*<<< orphan*/  transfer_len; TYPE_6__* cmd; } ;
struct nvmet_rdma_rsp {TYPE_5__ req; int /*<<< orphan*/  flags; TYPE_2__* queue; } ;
struct nvme_sgl_desc {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {struct nvme_sgl_desc sgl; } ;
struct TYPE_10__ {TYPE_3__ dptr; } ;
struct TYPE_12__ {TYPE_4__ common; } ;
struct TYPE_8__ {TYPE_1__* dev; } ;
struct TYPE_7__ {scalar_t__ inline_data_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVMET_RDMA_REQ_INLINE_DATA ; 
 int NVME_SC_DNR ; 
 int NVME_SC_INVALID_FIELD ; 
 int NVME_SC_SGL_INVALID_OFFSET ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_is_write (TYPE_6__*) ; 
 int /*<<< orphan*/  nvmet_rdma_use_inline_sg (struct nvmet_rdma_rsp*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static u16 nvmet_rdma_map_sgl_inline(struct nvmet_rdma_rsp *rsp)
{
	struct nvme_sgl_desc *sgl = &rsp->req.cmd->common.dptr.sgl;
	u64 off = le64_to_cpu(sgl->addr);
	u32 len = le32_to_cpu(sgl->length);

	if (!nvme_is_write(rsp->req.cmd))
		return NVME_SC_INVALID_FIELD | NVME_SC_DNR;

	if (off + len > rsp->queue->dev->inline_data_size) {
		pr_err("invalid inline data offset!\n");
		return NVME_SC_SGL_INVALID_OFFSET | NVME_SC_DNR;
	}

	/* no data command? */
	if (!len)
		return 0;

	nvmet_rdma_use_inline_sg(rsp, len, off);
	rsp->flags |= NVMET_RDMA_REQ_INLINE_DATA;
	rsp->req.transfer_len += len;
	return 0;
}
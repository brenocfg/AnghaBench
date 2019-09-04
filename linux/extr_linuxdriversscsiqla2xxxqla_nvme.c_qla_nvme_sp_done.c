#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rsp_pyld_len; struct nvmefc_fcp_req* desc; } ;
struct TYPE_7__ {TYPE_1__ nvme; } ;
struct srb_iocb {TYPE_2__ u; } ;
struct nvmefc_fcp_req {int /*<<< orphan*/  (* done ) (struct nvmefc_fcp_req*) ;int /*<<< orphan*/  rcv_rsplen; scalar_t__ status; } ;
struct TYPE_8__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_9__ {int /*<<< orphan*/  qpair; int /*<<< orphan*/  ref_count; TYPE_3__ u; } ;
typedef  TYPE_4__ srb_t ;

/* Variables and functions */
 scalar_t__ NVME_SC_INTERNAL ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2xxx_rel_qpair_sp (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (struct nvmefc_fcp_req*) ; 

__attribute__((used)) static void qla_nvme_sp_done(void *ptr, int res)
{
	srb_t *sp = ptr;
	struct srb_iocb *nvme;
	struct nvmefc_fcp_req *fd;

	nvme = &sp->u.iocb_cmd;
	fd = nvme->u.nvme.desc;

	if (!atomic_dec_and_test(&sp->ref_count))
		return;

	if (res == QLA_SUCCESS)
		fd->status = 0;
	else
		fd->status = NVME_SC_INTERNAL;

	fd->rcv_rsplen = nvme->u.nvme.rsp_pyld_len;
	fd->done(fd);
	qla2xxx_rel_qpair_sp(sp->qpair, sp);

	return;
}
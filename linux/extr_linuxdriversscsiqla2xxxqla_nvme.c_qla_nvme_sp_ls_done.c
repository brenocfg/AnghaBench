#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct nvmefc_ls_req* desc; } ;
struct TYPE_11__ {TYPE_3__ nvme; } ;
struct srb_iocb {TYPE_4__ u; } ;
struct nvmefc_ls_req {struct nvme_private* private; } ;
struct nvme_private {int comp_status; int /*<<< orphan*/  ls_work; } ;
struct TYPE_9__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_12__ {TYPE_2__ u; int /*<<< orphan*/  ref_count; TYPE_1__* fcport; } ;
typedef  TYPE_5__ srb_t ;
struct TYPE_8__ {int /*<<< orphan*/  vha; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,TYPE_5__*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla2x00_rel_sp (TYPE_5__*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qla_nvme_sp_ls_done(void *ptr, int res)
{
	srb_t *sp = ptr;
	struct srb_iocb *nvme;
	struct nvmefc_ls_req   *fd;
	struct nvme_private *priv;

	if (atomic_read(&sp->ref_count) == 0) {
		ql_log(ql_log_warn, sp->fcport->vha, 0x2123,
		    "SP reference-count to ZERO on LS_done -- sp=%p.\n", sp);
		return;
	}

	if (!atomic_dec_and_test(&sp->ref_count))
		return;

	if (res)
		res = -EINVAL;

	nvme = &sp->u.iocb_cmd;
	fd = nvme->u.nvme.desc;
	priv = fd->private;
	priv->comp_status = res;
	schedule_work(&priv->ls_work);
	/* work schedule doesn't need the sp */
	qla2x00_rel_sp(sp);
}
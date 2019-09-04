#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * rsp; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  rsp_allocated_size; int /*<<< orphan*/ * req; int /*<<< orphan*/  req_dma; int /*<<< orphan*/  req_allocated_size; } ;
struct TYPE_12__ {int /*<<< orphan*/  els_resp_pyld_dma; int /*<<< orphan*/ * els_resp_pyld; int /*<<< orphan*/  rx_size; int /*<<< orphan*/  els_plogi_pyld_dma; int /*<<< orphan*/ * els_plogi_pyld; int /*<<< orphan*/  tx_size; } ;
struct TYPE_16__ {TYPE_4__ ctarg; TYPE_1__ els_plogi; } ;
struct srb_iocb {TYPE_5__ u; } ;
struct TYPE_17__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_18__ {int type; int /*<<< orphan*/  (* free ) (TYPE_7__*) ;TYPE_6__ u; } ;
typedef  TYPE_7__ srb_t ;
struct TYPE_19__ {TYPE_3__* hw; } ;
typedef  TYPE_8__ scsi_qla_host_t ;
struct TYPE_14__ {TYPE_2__* pdev; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  SRB_CT_PTHRU_CMD 129 
#define  SRB_ELS_DCMD 128 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 

void qla24xx_sp_unmap(scsi_qla_host_t *vha, srb_t *sp)
{
	struct srb_iocb *c = &sp->u.iocb_cmd;

	switch (sp->type) {
	case SRB_ELS_DCMD:
		if (c->u.els_plogi.els_plogi_pyld)
			dma_free_coherent(&vha->hw->pdev->dev,
			    c->u.els_plogi.tx_size,
			    c->u.els_plogi.els_plogi_pyld,
			    c->u.els_plogi.els_plogi_pyld_dma);

		if (c->u.els_plogi.els_resp_pyld)
			dma_free_coherent(&vha->hw->pdev->dev,
			    c->u.els_plogi.rx_size,
			    c->u.els_plogi.els_resp_pyld,
			    c->u.els_plogi.els_resp_pyld_dma);
		break;
	case SRB_CT_PTHRU_CMD:
	default:
		if (sp->u.iocb_cmd.u.ctarg.req) {
			dma_free_coherent(&vha->hw->pdev->dev,
			    sp->u.iocb_cmd.u.ctarg.req_allocated_size,
			    sp->u.iocb_cmd.u.ctarg.req,
			    sp->u.iocb_cmd.u.ctarg.req_dma);
			sp->u.iocb_cmd.u.ctarg.req = NULL;
		}

		if (sp->u.iocb_cmd.u.ctarg.rsp) {
			dma_free_coherent(&vha->hw->pdev->dev,
			    sp->u.iocb_cmd.u.ctarg.rsp_allocated_size,
			    sp->u.iocb_cmd.u.ctarg.rsp,
			    sp->u.iocb_cmd.u.ctarg.rsp_dma);
			sp->u.iocb_cmd.u.ctarg.rsp = NULL;
		}
		break;
	}

	sp->free(sp);
}
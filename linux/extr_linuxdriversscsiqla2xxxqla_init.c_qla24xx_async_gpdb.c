#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_16__ {int /*<<< orphan*/  in_dma; void* in; int /*<<< orphan*/ * out_mb; } ;
struct TYPE_17__ {TYPE_3__ mbx; } ;
struct srb_iocb {TYPE_4__ u; int /*<<< orphan*/  timeout; } ;
struct TYPE_14__ {int /*<<< orphan*/  online; } ;
struct scsi_qla_host {int /*<<< orphan*/  vp_idx; TYPE_1__ flags; struct qla_hw_data* hw; } ;
struct qla_hw_data {int /*<<< orphan*/  s_dma_pool; } ;
struct port_database_24xx {int dummy; } ;
struct TYPE_15__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_18__ {char* name; int /*<<< orphan*/  (* free ) (TYPE_5__*) ;int /*<<< orphan*/  handle; int /*<<< orphan*/  done; TYPE_2__ u; int /*<<< orphan*/  gen2; int /*<<< orphan*/  gen1; int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ srb_t ;
struct TYPE_19__ {int flags; int /*<<< orphan*/  port_name; int /*<<< orphan*/  loop_id; int /*<<< orphan*/  login_gen; int /*<<< orphan*/  rscn_gen; int /*<<< orphan*/  disc_state; } ;
typedef  TYPE_6__ fc_port_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSC_GPDB ; 
 int FCF_ASYNC_SENT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LSW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBC_GET_PORT_DATABASE ; 
 int /*<<< orphan*/  MSD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSW (int /*<<< orphan*/ ) ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_MB_IOCB ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct port_database_24xx*,int /*<<< orphan*/ ) ; 
 struct port_database_24xx* dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_disc ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla24xx_async_gpdb_sp_done ; 
 int /*<<< orphan*/  qla24xx_post_gpdb_work (struct scsi_qla_host*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_async_iocb_timeout ; 
 scalar_t__ qla2x00_get_async_timeout (struct scsi_qla_host*) ; 
 TYPE_5__* qla2x00_get_sp (struct scsi_qla_host*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_init_timer (TYPE_5__*,scalar_t__) ; 
 int qla2x00_start_sp (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

int qla24xx_async_gpdb(struct scsi_qla_host *vha, fc_port_t *fcport, u8 opt)
{
	srb_t *sp;
	struct srb_iocb *mbx;
	int rval = QLA_FUNCTION_FAILED;
	u16 *mb;
	dma_addr_t pd_dma;
	struct port_database_24xx *pd;
	struct qla_hw_data *ha = vha->hw;

	if (!vha->flags.online || (fcport->flags & FCF_ASYNC_SENT))
		return rval;

	fcport->disc_state = DSC_GPDB;

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	if (!sp)
		goto done;

	fcport->flags |= FCF_ASYNC_SENT;
	sp->type = SRB_MB_IOCB;
	sp->name = "gpdb";
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;

	mbx = &sp->u.iocb_cmd;
	mbx->timeout = qla2x00_async_iocb_timeout;
	qla2x00_init_timer(sp, qla2x00_get_async_timeout(vha) + 2);

	pd = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &pd_dma);
	if (pd == NULL) {
		ql_log(ql_log_warn, vha, 0xd043,
		    "Failed to allocate port database structure.\n");
		goto done_free_sp;
	}

	mb = sp->u.iocb_cmd.u.mbx.out_mb;
	mb[0] = MBC_GET_PORT_DATABASE;
	mb[1] = fcport->loop_id;
	mb[2] = MSW(pd_dma);
	mb[3] = LSW(pd_dma);
	mb[6] = MSW(MSD(pd_dma));
	mb[7] = LSW(MSD(pd_dma));
	mb[9] = vha->vp_idx;
	mb[10] = opt;

	mbx->u.mbx.in = (void *)pd;
	mbx->u.mbx.in_dma = pd_dma;

	sp->done = qla24xx_async_gpdb_sp_done;

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS)
		goto done_free_sp;

	ql_dbg(ql_dbg_disc, vha, 0x20dc,
	    "Async-%s %8phC hndl %x opt %x\n",
	    sp->name, fcport->port_name, sp->handle, opt);

	return rval;

done_free_sp:
	if (pd)
		dma_pool_free(ha->s_dma_pool, pd, pd_dma);

	sp->free(sp);
	fcport->flags &= ~FCF_ASYNC_SENT;
done:
	qla24xx_post_gpdb_work(vha, fcport, opt);
	return rval;
}
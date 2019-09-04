#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_8__ {int /*<<< orphan*/ * ptr; } ;
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;TYPE_4__ SCp; int /*<<< orphan*/  retries; int /*<<< orphan*/  allowed; int /*<<< orphan*/ * cmnd; TYPE_3__* device; } ;
struct qedf_ioreq {int /*<<< orphan*/  refcount; struct scsi_cmnd* sc_cmd; int /*<<< orphan*/  fcport; int /*<<< orphan*/  xid; } ;
struct qedf_ctx {TYPE_2__* lport; int /*<<< orphan*/  dbg_ctx; } ;
struct TYPE_7__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__* host; } ;
struct TYPE_5__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  QEDF_INFO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct scsi_cmnd*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QEDF_IO_TRACE_RSP ; 
 int /*<<< orphan*/  QEDF_LOG_IO ; 
 int /*<<< orphan*/  QEDF_WARN (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int kref_read (int /*<<< orphan*/ *) ; 
 scalar_t__ qedf_io_tracing ; 
 int /*<<< orphan*/  qedf_release_cmd ; 
 int /*<<< orphan*/  qedf_trace_io (int /*<<< orphan*/ ,struct qedf_ioreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_unmap_sg_list (struct qedf_ctx*,struct qedf_ioreq*) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_set_resid (struct scsi_cmnd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

void qedf_scsi_done(struct qedf_ctx *qedf, struct qedf_ioreq *io_req,
	int result)
{
	u16 xid;
	struct scsi_cmnd *sc_cmd;
	int refcount;

	if (!io_req)
		return;

	xid = io_req->xid;
	sc_cmd = io_req->sc_cmd;

	if (!sc_cmd) {
		QEDF_WARN(&(qedf->dbg_ctx), "sc_cmd is NULL!\n");
		return;
	}

	if (!sc_cmd->SCp.ptr) {
		QEDF_WARN(&(qedf->dbg_ctx), "SCp.ptr is NULL, returned in "
		    "another context.\n");
		return;
	}

	qedf_unmap_sg_list(qedf, io_req);

	sc_cmd->result = result << 16;
	refcount = kref_read(&io_req->refcount);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO, "%d:0:%d:%lld: Completing "
	    "sc_cmd=%p result=0x%08x op=0x%02x lba=0x%02x%02x%02x%02x, "
	    "allowed=%d retries=%d refcount=%d.\n",
	    qedf->lport->host->host_no, sc_cmd->device->id,
	    sc_cmd->device->lun, sc_cmd, sc_cmd->result, sc_cmd->cmnd[0],
	    sc_cmd->cmnd[2], sc_cmd->cmnd[3], sc_cmd->cmnd[4],
	    sc_cmd->cmnd[5], sc_cmd->allowed, sc_cmd->retries,
	    refcount);

	/*
	 * Set resid to the whole buffer length so we won't try to resue any
	 * previously read data
	 */
	scsi_set_resid(sc_cmd, scsi_bufflen(sc_cmd));

	if (qedf_io_tracing)
		qedf_trace_io(io_req->fcport, io_req, QEDF_IO_TRACE_RSP);

	io_req->sc_cmd = NULL;
	sc_cmd->SCp.ptr = NULL;
	sc_cmd->scsi_done(sc_cmd);
	kref_put(&io_req->refcount, qedf_release_cmd);
}
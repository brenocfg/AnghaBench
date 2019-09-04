#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* free ) (TYPE_1__*) ;int /*<<< orphan*/  ref_count; int /*<<< orphan*/  vha; } ;
typedef  TYPE_1__ srb_t ;

/* Variables and functions */
 struct scsi_cmnd* GET_CMD_SP (TYPE_1__*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int ql2xextended_error_logging ; 
 int /*<<< orphan*/  ql_dbg (int,int /*<<< orphan*/ ,int,char*,TYPE_1__*,struct scsi_cmnd*) ; 
 int ql_dbg_io ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (struct scsi_cmnd*) ; 

void
qla2x00_sp_compl(void *ptr, int res)
{
	srb_t *sp = ptr;
	struct scsi_cmnd *cmd = GET_CMD_SP(sp);

	cmd->result = res;

	if (atomic_read(&sp->ref_count) == 0) {
		ql_dbg(ql_dbg_io, sp->vha, 0x3015,
		    "SP reference-count to ZERO -- sp=%p cmd=%p.\n",
		    sp, GET_CMD_SP(sp));
		if (ql2xextended_error_logging & ql_dbg_io)
			WARN_ON(atomic_read(&sp->ref_count) == 0);
		return;
	}
	if (!atomic_dec_and_test(&sp->ref_count))
		return;

	sp->free(sp);
	cmd->scsi_done(cmd);
}
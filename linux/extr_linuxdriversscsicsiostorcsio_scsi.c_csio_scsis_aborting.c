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
struct csio_scsim {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sm_list; } ;
struct csio_ioreq {TYPE_2__ sm; int /*<<< orphan*/  wr_status; int /*<<< orphan*/  drv_status; TYPE_1__* lnode; } ;
struct csio_hw {int dummy; } ;
typedef  enum csio_scsi_ev { ____Placeholder_csio_scsi_ev } csio_scsi_ev ;
struct TYPE_3__ {struct csio_hw* hwp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_DEC_STATS (struct csio_scsim*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_scsim*,int /*<<< orphan*/ ) ; 
#define  CSIO_SCSIE_ABORT 132 
#define  CSIO_SCSIE_ABORTED 131 
#define  CSIO_SCSIE_CLOSE 130 
#define  CSIO_SCSIE_COMPLETED 129 
#define  CSIO_SCSIE_DRVCLEANUP 128 
 int /*<<< orphan*/  ECANCELED ; 
 int /*<<< orphan*/  FW_EINVAL ; 
 int /*<<< orphan*/  FW_HOSTERROR ; 
 int /*<<< orphan*/  FW_SCSI_ABORT_REQUESTED ; 
 int /*<<< orphan*/  FW_SUCCESS ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*,...) ; 
 struct csio_scsim* csio_hw_to_scsim (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_scsi_itnexus_loss_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_scsis_uninit ; 
 int /*<<< orphan*/  csio_set_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_warn (struct csio_hw*,char*,struct csio_ioreq*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_abrt_dups ; 
 int /*<<< orphan*/  n_active ; 

__attribute__((used)) static void
csio_scsis_aborting(struct csio_ioreq *req, enum csio_scsi_ev evt)
{
	struct csio_hw *hw = req->lnode->hwp;
	struct csio_scsim *scm = csio_hw_to_scsim(hw);

	switch (evt) {
	case CSIO_SCSIE_COMPLETED:
		csio_dbg(hw,
			 "ioreq %p recvd cmpltd (wr_status:%d) "
			 "in aborting st\n", req, req->wr_status);
		/*
		 * Use -ECANCELED to explicitly tell the ABORTED event that
		 * the original I/O was returned to driver by FW.
		 * We dont really care if the I/O was returned with success by
		 * FW (because the ABORT and completion of the I/O crossed each
		 * other), or any other return value. Once we are in aborting
		 * state, the success or failure of the I/O is unimportant to
		 * us.
		 */
		req->drv_status = -ECANCELED;
		break;

	case CSIO_SCSIE_ABORT:
		CSIO_INC_STATS(scm, n_abrt_dups);
		break;

	case CSIO_SCSIE_ABORTED:

		csio_dbg(hw, "abort of %p return status:0x%x drv_status:%x\n",
			 req, req->wr_status, req->drv_status);
		/*
		 * Check if original I/O WR completed before the Abort
		 * completion.
		 */
		if (req->drv_status != -ECANCELED) {
			csio_warn(hw,
				  "Abort completed before original I/O,"
				   " req:%p\n", req);
			CSIO_DB_ASSERT(0);
		}

		/*
		 * There are the following possible scenarios:
		 * 1. The abort completed successfully, FW returned FW_SUCCESS.
		 * 2. The completion of an I/O and the receipt of
		 *    abort for that I/O by the FW crossed each other.
		 *    The FW returned FW_EINVAL. The original I/O would have
		 *    returned with FW_SUCCESS or any other SCSI error.
		 * 3. The FW couldnt sent the abort out on the wire, as there
		 *    was an I-T nexus loss (link down, remote device logged
		 *    out etc). FW sent back an appropriate IT nexus loss status
		 *    for the abort.
		 * 4. FW sent an abort, but abort timed out (remote device
		 *    didnt respond). FW replied back with
		 *    FW_SCSI_ABORT_TIMEDOUT.
		 * 5. FW couldnt genuinely abort the request for some reason,
		 *    and sent us an error.
		 *
		 * The first 3 scenarios are treated as  succesful abort
		 * operations by the host, while the last 2 are failed attempts
		 * to abort. Manipulate the return value of the request
		 * appropriately, so that host can convey these results
		 * back to the upper layer.
		 */
		if ((req->wr_status == FW_SUCCESS) ||
		    (req->wr_status == FW_EINVAL) ||
		    csio_scsi_itnexus_loss_error(req->wr_status))
			req->wr_status = FW_SCSI_ABORT_REQUESTED;

		CSIO_DEC_STATS(scm, n_active);
		list_del_init(&req->sm.sm_list);
		csio_set_state(&req->sm, csio_scsis_uninit);
		break;

	case CSIO_SCSIE_DRVCLEANUP:
		req->wr_status = FW_HOSTERROR;
		CSIO_DEC_STATS(scm, n_active);
		csio_set_state(&req->sm, csio_scsis_uninit);
		break;

	case CSIO_SCSIE_CLOSE:
		/*
		 * We can receive this event from the module
		 * cleanup paths, if the FW forgot to reply to the ABORT WR
		 * and left this ioreq in this state. For now, just ignore
		 * the event. The CLOSE event is sent to this state, as
		 * the LINK may have already gone down.
		 */
		break;

	default:
		csio_dbg(hw, "Unhandled event:%d sent to req:%p\n", evt, req);
		CSIO_DB_ASSERT(0);
	}
}
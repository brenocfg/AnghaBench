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
struct csio_scsim {int /*<<< orphan*/  active_q; } ;
struct TYPE_4__ {int /*<<< orphan*/  sm_list; } ;
struct csio_ioreq {int /*<<< orphan*/  drv_status; int /*<<< orphan*/  eq_idx; TYPE_2__ sm; int /*<<< orphan*/  dcopy; int /*<<< orphan*/  datadir; int /*<<< orphan*/  nsge; TYPE_1__* lnode; } ;
struct csio_hw {int dummy; } ;
typedef  enum csio_scsi_ev { ____Placeholder_csio_scsi_ev } csio_scsi_ev ;
struct TYPE_3__ {struct csio_hw* hwp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_scsim*,int /*<<< orphan*/ ) ; 
#define  CSIO_SCSIE_ABORT 131 
#define  CSIO_SCSIE_CLOSE 130 
#define  CSIO_SCSIE_START_IO 129 
#define  CSIO_SCSIE_START_TM 128 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  csio_dbg (struct csio_hw*,char*,int,struct csio_ioreq*) ; 
 struct csio_scsim* csio_hw_to_scsim (struct csio_hw*) ; 
 int /*<<< orphan*/  csio_scsi_cmd (struct csio_ioreq*) ; 
 int /*<<< orphan*/  csio_scsi_write (struct csio_ioreq*) ; 
 int /*<<< orphan*/  csio_scsis_io_active ; 
 int /*<<< orphan*/  csio_scsis_tm_active ; 
 int /*<<< orphan*/  csio_set_state (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csio_setup_ddp (struct csio_scsim*,struct csio_ioreq*) ; 
 int /*<<< orphan*/  csio_warn (struct csio_hw*,char*,struct csio_ioreq*) ; 
 int /*<<< orphan*/  csio_wr_issue (struct csio_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  likely (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  n_active ; 
 int /*<<< orphan*/  n_tm_active ; 

__attribute__((used)) static void
csio_scsis_uninit(struct csio_ioreq *req, enum csio_scsi_ev evt)
{
	struct csio_hw *hw = req->lnode->hwp;
	struct csio_scsim *scsim = csio_hw_to_scsim(hw);

	switch (evt) {
	case CSIO_SCSIE_START_IO:

		if (req->nsge) {
			if (req->datadir == DMA_TO_DEVICE) {
				req->dcopy = 0;
				csio_scsi_write(req);
			} else
				csio_setup_ddp(scsim, req);
		} else {
			csio_scsi_cmd(req);
		}

		if (likely(req->drv_status == 0)) {
			/* change state and enqueue on active_q */
			csio_set_state(&req->sm, csio_scsis_io_active);
			list_add_tail(&req->sm.sm_list, &scsim->active_q);
			csio_wr_issue(hw, req->eq_idx, false);
			CSIO_INC_STATS(scsim, n_active);

			return;
		}
		break;

	case CSIO_SCSIE_START_TM:
		csio_scsi_cmd(req);
		if (req->drv_status == 0) {
			/*
			 * NOTE: We collect the affected I/Os prior to issuing
			 * LUN reset, and not after it. This is to prevent
			 * aborting I/Os that get issued after the LUN reset,
			 * but prior to LUN reset completion (in the event that
			 * the host stack has not blocked I/Os to a LUN that is
			 * being reset.
			 */
			csio_set_state(&req->sm, csio_scsis_tm_active);
			list_add_tail(&req->sm.sm_list, &scsim->active_q);
			csio_wr_issue(hw, req->eq_idx, false);
			CSIO_INC_STATS(scsim, n_tm_active);
		}
		return;

	case CSIO_SCSIE_ABORT:
	case CSIO_SCSIE_CLOSE:
		/*
		 * NOTE:
		 * We could get here due to  :
		 * - a window in the cleanup path of the SCSI module
		 *   (csio_scsi_abort_io()). Please see NOTE in this function.
		 * - a window in the time we tried to issue an abort/close
		 *   of a request to FW, and the FW completed the request
		 *   itself.
		 *   Print a message for now, and return INVAL either way.
		 */
		req->drv_status = -EINVAL;
		csio_warn(hw, "Trying to abort/close completed IO:%p!\n", req);
		break;

	default:
		csio_dbg(hw, "Unhandled event:%d sent to req:%p\n", evt, req);
		CSIO_DB_ASSERT(0);
	}
}
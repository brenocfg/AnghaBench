#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct fc_seq {int dummy; } ;
struct fc_lport {int dummy; } ;
struct fc_frame {int dummy; } ;
struct fc_fcp_pkt {int state; scalar_t__ cdb_status; scalar_t__ xfer_len; scalar_t__ data_len; int scsi_comp_flags; scalar_t__ scsi_resid; scalar_t__ cmd; struct fc_lport* lp; struct fc_seq* seq_ptr; scalar_t__ status_code; int /*<<< orphan*/  io_status; } ;
struct fc_exch {int /*<<< orphan*/  sid; int /*<<< orphan*/  did; } ;

/* Variables and functions */
 int FCP_CONF_REQ ; 
 int FCP_RESID_UNDER ; 
 scalar_t__ FC_CMD_ABORTED ; 
 scalar_t__ FC_DATA_UNDRUN ; 
 int /*<<< orphan*/  FC_FCP_DBG (struct fc_fcp_pkt*,char*,scalar_t__,scalar_t__) ; 
 int FC_FC_END_SEQ ; 
 int FC_FC_LAST_SEQ ; 
 int FC_FC_SEQ_INIT ; 
 int /*<<< orphan*/  FC_RCTL_DD_SOL_CTL ; 
 int FC_SRB_ABORTED ; 
 int FC_SRB_ABORT_PENDING ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 scalar_t__ SAM_STAT_GOOD ; 
 int /*<<< orphan*/  fc_exch_done (struct fc_seq*) ; 
 struct fc_frame* fc_fcp_frame_alloc (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_fill_fc_hdr (struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_io_compl (struct fc_fcp_pkt*) ; 
 struct fc_exch* fc_seq_exch (struct fc_seq*) ; 
 int /*<<< orphan*/  fc_seq_send (struct fc_lport*,struct fc_seq*,struct fc_frame*) ; 
 struct fc_seq* fc_seq_start_next (struct fc_seq*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void fc_fcp_complete_locked(struct fc_fcp_pkt *fsp)
{
	struct fc_lport *lport = fsp->lp;
	struct fc_seq *seq;
	struct fc_exch *ep;
	u32 f_ctl;

	if (fsp->state & FC_SRB_ABORT_PENDING)
		return;

	if (fsp->state & FC_SRB_ABORTED) {
		if (!fsp->status_code)
			fsp->status_code = FC_CMD_ABORTED;
	} else {
		/*
		 * Test for transport underrun, independent of response
		 * underrun status.
		 */
		if (fsp->cdb_status == SAM_STAT_GOOD &&
		    fsp->xfer_len < fsp->data_len && !fsp->io_status &&
		    (!(fsp->scsi_comp_flags & FCP_RESID_UNDER) ||
		     fsp->xfer_len < fsp->data_len - fsp->scsi_resid)) {
			FC_FCP_DBG(fsp, "data underrun, xfer %zx data %x\n",
				    fsp->xfer_len, fsp->data_len);
			fsp->status_code = FC_DATA_UNDRUN;
		}
	}

	seq = fsp->seq_ptr;
	if (seq) {
		fsp->seq_ptr = NULL;
		if (unlikely(fsp->scsi_comp_flags & FCP_CONF_REQ)) {
			struct fc_frame *conf_frame;
			struct fc_seq *csp;

			csp = fc_seq_start_next(seq);
			conf_frame = fc_fcp_frame_alloc(fsp->lp, 0);
			if (conf_frame) {
				f_ctl = FC_FC_SEQ_INIT;
				f_ctl |= FC_FC_LAST_SEQ | FC_FC_END_SEQ;
				ep = fc_seq_exch(seq);
				fc_fill_fc_hdr(conf_frame, FC_RCTL_DD_SOL_CTL,
					       ep->did, ep->sid,
					       FC_TYPE_FCP, f_ctl, 0);
				fc_seq_send(lport, csp, conf_frame);
			}
		}
		fc_exch_done(seq);
	}
	/*
	 * Some resets driven by SCSI are not I/Os and do not have
	 * SCSI commands associated with the requests. We should not
	 * call I/O completion if we do not have a SCSI command.
	 */
	if (fsp->cmd)
		fc_io_compl(fsp);
}
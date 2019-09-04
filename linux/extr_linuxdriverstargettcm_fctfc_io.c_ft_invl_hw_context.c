#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ft_cmd {scalar_t__ was_ddp_setup; int /*<<< orphan*/  write_data_len; struct fc_seq* seq; } ;
struct fc_seq {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ddp_done ) (struct fc_lport*,scalar_t__) ;} ;
struct fc_lport {scalar_t__ lro_xid; TYPE_1__ tt; } ;
struct fc_exch {scalar_t__ xid; struct fc_lport* lp; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct fc_exch* fc_seq_exch (struct fc_seq*) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,scalar_t__) ; 

void ft_invl_hw_context(struct ft_cmd *cmd)
{
	struct fc_seq *seq;
	struct fc_exch *ep = NULL;
	struct fc_lport *lport = NULL;

	BUG_ON(!cmd);
	seq = cmd->seq;

	/* Cleanup the DDP context in HW if DDP was setup */
	if (cmd->was_ddp_setup && seq) {
		ep = fc_seq_exch(seq);
		if (ep) {
			lport = ep->lp;
			if (lport && (ep->xid <= lport->lro_xid)) {
				/*
				 * "ddp_done" trigger invalidation of HW
				 * specific DDP context
				 */
				cmd->write_data_len = lport->tt.ddp_done(lport,
								      ep->xid);

				/*
				 * Resetting same variable to indicate HW's
				 * DDP context has been invalidated to avoid
				 * re_invalidation of same context (context is
				 * identified using ep->xid)
				 */
				cmd->was_ddp_setup = 0;
			}
		}
	}
}
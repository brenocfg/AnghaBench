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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa; } ;
struct bfad_hal_comp {scalar_t__ status; int /*<<< orphan*/  comp; } ;
struct bfa_cb_pending_q_s {int dummy; } ;
struct bfa_bsg_gen_s {scalar_t__ status; } ;
typedef  int /*<<< orphan*/  bfa_cb_cbfn_t ;

/* Variables and functions */
 scalar_t__ BFA_STATUS_OK ; 
 scalar_t__ bfa_fcport_clear_stats (int /*<<< orphan*/ *,struct bfa_cb_pending_q_s*) ; 
 int /*<<< orphan*/  bfa_pending_q_init (struct bfa_cb_pending_q_s*,int /*<<< orphan*/ ,struct bfad_hal_comp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,scalar_t__) ; 
 scalar_t__ bfad_hcb_comp ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
bfad_iocmd_fcport_reset_stats(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_gen_s *iocmd = (struct bfa_bsg_gen_s *)cmd;
	struct bfad_hal_comp fcomp;
	unsigned long	flags;
	struct bfa_cb_pending_q_s cb_qe;

	init_completion(&fcomp.comp);
	bfa_pending_q_init(&cb_qe, (bfa_cb_cbfn_t)bfad_hcb_comp, &fcomp, NULL);

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcport_clear_stats(&bfad->bfa, &cb_qe);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	if (iocmd->status != BFA_STATUS_OK) {
		bfa_trc(bfad, iocmd->status);
		goto out;
	}
	wait_for_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
out:
	return 0;
}
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
struct bfa_bsg_fcpim_s {int /*<<< orphan*/  status; int /*<<< orphan*/  param; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_fcpim_path_tov_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_cfg_fcpim(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_fcpim_s *iocmd = (struct bfa_bsg_fcpim_s *)cmd;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	bfa_fcpim_path_tov_set(&bfad->bfa, iocmd->param);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
	return 0;
}
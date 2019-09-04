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
struct bfa_bsg_fcpim_lunmask_s {int /*<<< orphan*/  lun; int /*<<< orphan*/  rpwwn; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  vf_id; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 unsigned int IOCMD_FCPIM_LUNMASK_ADD ; 
 unsigned int IOCMD_FCPIM_LUNMASK_DELETE ; 
 int /*<<< orphan*/  bfa_fcpim_lunmask_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcpim_lunmask_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_fcpim_cfg_lunmask(struct bfad_s *bfad, void *cmd, unsigned int v_cmd)
{
	struct bfa_bsg_fcpim_lunmask_s *iocmd =
				(struct bfa_bsg_fcpim_lunmask_s *)cmd;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	if (v_cmd == IOCMD_FCPIM_LUNMASK_ADD)
		iocmd->status = bfa_fcpim_lunmask_add(&bfad->bfa, iocmd->vf_id,
					&iocmd->pwwn, iocmd->rpwwn, iocmd->lun);
	else if (v_cmd == IOCMD_FCPIM_LUNMASK_DELETE)
		iocmd->status = bfa_fcpim_lunmask_delete(&bfad->bfa,
					iocmd->vf_id, &iocmd->pwwn,
					iocmd->rpwwn, iocmd->lun);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	return 0;
}
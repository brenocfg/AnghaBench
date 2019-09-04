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
typedef  union bfa_port_stats_u {int dummy; } bfa_port_stats_u ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {TYPE_1__ modules; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; TYPE_2__ bfa; } ;
struct bfad_hal_comp {scalar_t__ status; int /*<<< orphan*/  comp; } ;
struct bfa_bsg_port_stats_s {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ BFA_STATUS_OK ; 
 scalar_t__ BFA_STATUS_VERSION_FAIL ; 
 scalar_t__ bfa_port_get_stats (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,struct bfad_hal_comp*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,scalar_t__) ; 
 scalar_t__ bfad_chk_iocmd_sz (unsigned int,int,int) ; 
 int /*<<< orphan*/  bfad_hcb_comp ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
bfad_iocmd_port_get_stats(struct bfad_s *bfad, void *cmd,
			unsigned int payload_len)
{
	struct bfa_bsg_port_stats_s *iocmd = (struct bfa_bsg_port_stats_s *)cmd;
	struct bfad_hal_comp fcomp;
	void	*iocmd_bufptr;
	unsigned long	flags;

	if (bfad_chk_iocmd_sz(payload_len,
			sizeof(struct bfa_bsg_port_stats_s),
			sizeof(union bfa_port_stats_u)) != BFA_STATUS_OK) {
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		return 0;
	}

	iocmd_bufptr = (char *)iocmd + sizeof(struct bfa_bsg_port_stats_s);

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_port_get_stats(&bfad->bfa.modules.port,
				iocmd_bufptr, bfad_hcb_comp, &fcomp);
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
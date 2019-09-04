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
struct bfa_bsg_phy_s {scalar_t__ status; int /*<<< orphan*/  bufsz; int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_PHY (int /*<<< orphan*/ *) ; 
 scalar_t__ BFA_STATUS_OK ; 
 scalar_t__ BFA_STATUS_VERSION_FAIL ; 
 scalar_t__ bfa_phy_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfad_hal_comp*) ; 
 scalar_t__ bfad_chk_iocmd_sz (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfad_hcb_comp ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
bfad_iocmd_phy_read(struct bfad_s *bfad, void *cmd, unsigned int payload_len)
{
	struct bfa_bsg_phy_s *iocmd = (struct bfa_bsg_phy_s *)cmd;
	struct bfad_hal_comp fcomp;
	void	*iocmd_bufptr;
	unsigned long	flags;

	if (bfad_chk_iocmd_sz(payload_len,
			sizeof(struct bfa_bsg_phy_s),
			iocmd->bufsz) != BFA_STATUS_OK) {
		iocmd->status = BFA_STATUS_VERSION_FAIL;
		return 0;
	}

	iocmd_bufptr = (char *)iocmd + sizeof(struct bfa_bsg_phy_s);
	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_phy_read(BFA_PHY(&bfad->bfa),
				iocmd->instance, iocmd_bufptr, iocmd->bufsz,
				0, bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	if (iocmd->status != BFA_STATUS_OK)
		goto out;
	wait_for_completion(&fcomp.comp);
	iocmd->status = fcomp.status;
	if (iocmd->status != BFA_STATUS_OK)
		goto out;
out:
	return 0;
}
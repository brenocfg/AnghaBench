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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {TYPE_1__ modules; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; TYPE_2__ bfa; } ;
struct bfad_im_port_s {struct bfad_s* bfad; } ;
struct bfad_hal_comp {scalar_t__ status; int /*<<< orphan*/  comp; } ;
struct Scsi_Host {scalar_t__* hostdata; } ;

/* Variables and functions */
 scalar_t__ BFA_STATUS_OK ; 
 int EIO ; 
 scalar_t__ bfa_port_disable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfad_hal_comp*) ; 
 scalar_t__ bfa_port_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfad_hal_comp*) ; 
 int /*<<< orphan*/  bfad_hcb_comp ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int
bfad_im_issue_fc_host_lip(struct Scsi_Host *shost)
{
	struct bfad_im_port_s *im_port =
			(struct bfad_im_port_s *) shost->hostdata[0];
	struct bfad_s *bfad = im_port->bfad;
	struct bfad_hal_comp fcomp;
	unsigned long flags;
	uint32_t status;

	init_completion(&fcomp.comp);
	spin_lock_irqsave(&bfad->bfad_lock, flags);
	status = bfa_port_disable(&bfad->bfa.modules.port,
					bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	if (status != BFA_STATUS_OK)
		return -EIO;

	wait_for_completion(&fcomp.comp);
	if (fcomp.status != BFA_STATUS_OK)
		return -EIO;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	status = bfa_port_enable(&bfad->bfa.modules.port,
					bfad_hcb_comp, &fcomp);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	if (status != BFA_STATUS_OK)
		return -EIO;

	wait_for_completion(&fcomp.comp);
	if (fcomp.status != BFA_STATUS_OK)
		return -EIO;

	return 0;
}
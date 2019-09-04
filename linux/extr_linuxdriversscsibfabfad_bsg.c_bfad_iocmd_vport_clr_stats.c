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
struct bfad_s {int /*<<< orphan*/  bfad_lock; int /*<<< orphan*/  bfa_fcs; } ;
struct bfa_vport_stats_s {int dummy; } ;
struct bfa_lport_stats_s {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stats; } ;
struct bfa_fcs_vport_s {TYPE_1__ lport; int /*<<< orphan*/  vport_stats; } ;
struct bfa_bsg_reset_stats_s {int /*<<< orphan*/  status; int /*<<< orphan*/  vpwwn; int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_STATUS_UNKNOWN_VWWN ; 
 struct bfa_fcs_vport_s* bfa_fcs_vport_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_vport_clr_stats(struct bfad_s *bfad, void *cmd)
{
	struct bfa_fcs_vport_s *fcs_vport;
	struct bfa_bsg_reset_stats_s *iocmd =
				(struct bfa_bsg_reset_stats_s *)cmd;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	fcs_vport = bfa_fcs_vport_lookup(&bfad->bfa_fcs,
				iocmd->vf_id, iocmd->vpwwn);
	if (fcs_vport == NULL) {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		iocmd->status = BFA_STATUS_UNKNOWN_VWWN;
		goto out;
	}

	memset(&fcs_vport->vport_stats, 0, sizeof(struct bfa_vport_stats_s));
	memset(&fcs_vport->lport.stats, 0, sizeof(struct bfa_lport_stats_s));
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	iocmd->status = BFA_STATUS_OK;
out:
	return 0;
}
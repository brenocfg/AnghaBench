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
struct bfa_bsg_bbcr_enable_s {int status; int /*<<< orphan*/  bb_scn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int EINVAL ; 
 unsigned int IOCMD_PORT_BBCR_DISABLE ; 
 unsigned int IOCMD_PORT_BBCR_ENABLE ; 
 int bfa_fcport_cfg_bbcr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_port_cfg_bbcr(struct bfad_s *bfad, unsigned int cmd, void *pcmd)
{
	struct bfa_bsg_bbcr_enable_s *iocmd =
			(struct bfa_bsg_bbcr_enable_s *)pcmd;
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	if (cmd == IOCMD_PORT_BBCR_ENABLE)
		rc = bfa_fcport_cfg_bbcr(&bfad->bfa, BFA_TRUE, iocmd->bb_scn);
	else if (cmd == IOCMD_PORT_BBCR_DISABLE)
		rc = bfa_fcport_cfg_bbcr(&bfad->bfa, BFA_FALSE, 0);
	else {
		spin_unlock_irqrestore(&bfad->bfad_lock, flags);
		return -EINVAL;
	}
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	iocmd->status = rc;
	return 0;
}
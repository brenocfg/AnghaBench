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
struct TYPE_3__ {int /*<<< orphan*/  cee; } ;
struct TYPE_4__ {TYPE_1__ modules; } ;
struct bfad_s {int /*<<< orphan*/  bfad_lock; TYPE_2__ bfa; } ;
struct bfa_bsg_gen_s {scalar_t__ status; } ;

/* Variables and functions */
 scalar_t__ BFA_STATUS_OK ; 
 scalar_t__ bfa_cee_reset_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_cee_reset_stats(struct bfad_s *bfad, void *cmd)
{
	struct bfa_bsg_gen_s *iocmd = (struct bfa_bsg_gen_s *)cmd;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_cee_reset_stats(&bfad->bfa.modules.cee, NULL, NULL);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);
	if (iocmd->status != BFA_STATUS_OK)
		bfa_trc(bfad, 0x5555);
	return 0;
}
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
struct bfa_bsg_qos_bw_s {int /*<<< orphan*/  qos_bw; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_fcport_set_qos_bw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int
bfad_iocmd_qos_set_bw(struct bfad_s *bfad, void *pcmd)
{
	struct bfa_bsg_qos_bw_s *iocmd = (struct bfa_bsg_qos_bw_s *)pcmd;
	unsigned long	flags;

	spin_lock_irqsave(&bfad->bfad_lock, flags);
	iocmd->status = bfa_fcport_set_qos_bw(&bfad->bfa, &iocmd->qos_bw);
	spin_unlock_irqrestore(&bfad->bfad_lock, flags);

	return 0;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int check_nego; } ;
struct TYPE_5__ {scalar_t__ uval; int /*<<< orphan*/  wval; scalar_t__ sval; } ;
struct sym_tcb {int /*<<< orphan*/ * starget; TYPE_2__ tgoal; TYPE_1__ head; } ;
struct sym_lcb {scalar_t__ busy_itl; scalar_t__ busy_itlq; } ;
struct TYPE_8__ {TYPE_3__* host; } ;
struct sym_hcb {TYPE_4__ s; int /*<<< orphan*/  rv_scntl3; struct sym_tcb* target; } ;
struct scsi_device {size_t id; scalar_t__ lun; int /*<<< orphan*/  host; } ;
struct TYPE_7__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  starget_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sym_free_lcb (struct sym_hcb*,size_t,scalar_t__) ; 
 struct sym_hcb* sym_get_hcb (int /*<<< orphan*/ ) ; 
 struct sym_lcb* sym_lp (struct sym_tcb*,scalar_t__) ; 
 int /*<<< orphan*/  sym_reset_scsi_bus (struct sym_hcb*,int) ; 

__attribute__((used)) static void sym53c8xx_slave_destroy(struct scsi_device *sdev)
{
	struct sym_hcb *np = sym_get_hcb(sdev->host);
	struct sym_tcb *tp = &np->target[sdev->id];
	struct sym_lcb *lp = sym_lp(tp, sdev->lun);
	unsigned long flags;

	/* if slave_alloc returned before allocating a sym_lcb, return */
	if (!lp)
		return;

	spin_lock_irqsave(np->s.host->host_lock, flags);

	if (lp->busy_itlq || lp->busy_itl) {
		/*
		 * This really shouldn't happen, but we can't return an error
		 * so let's try to stop all on-going I/O.
		 */
		starget_printk(KERN_WARNING, tp->starget,
			       "Removing busy LCB (%d)\n", (u8)sdev->lun);
		sym_reset_scsi_bus(np, 1);
	}

	if (sym_free_lcb(np, sdev->id, sdev->lun) == 0) {
		/*
		 * It was the last unit for this target.
		 */
		tp->head.sval        = 0;
		tp->head.wval        = np->rv_scntl3;
		tp->head.uval        = 0;
		tp->tgoal.check_nego = 1;
		tp->starget	     = NULL;
	}

	spin_unlock_irqrestore(np->s.host->host_lock, flags);
}
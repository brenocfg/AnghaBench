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
struct TYPE_8__ {int /*<<< orphan*/  lpm; } ;
union orb {TYPE_4__ cmd; } ;
typedef  int /*<<< orphan*/  u32 ;
struct vfio_ccw_private {int /*<<< orphan*/  cp; int /*<<< orphan*/  state; struct subchannel* sch; } ;
struct TYPE_5__ {int /*<<< orphan*/  actl; } ;
struct TYPE_6__ {TYPE_1__ cmd; } ;
struct TYPE_7__ {TYPE_2__ scsw; } ;
struct subchannel {int /*<<< orphan*/  lock; int /*<<< orphan*/  lpm; TYPE_3__ schib; int /*<<< orphan*/  schid; } ;
typedef  scalar_t__ addr_t ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  SCSW_ACTL_START_PEND ; 
 int /*<<< orphan*/  VFIO_CCW_STATE_BUSY ; 
 int /*<<< orphan*/  cio_update_schib (struct subchannel*) ; 
 union orb* cp_get_orb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int ssch (int /*<<< orphan*/ ,union orb*) ; 

__attribute__((used)) static int fsm_io_helper(struct vfio_ccw_private *private)
{
	struct subchannel *sch;
	union orb *orb;
	int ccode;
	__u8 lpm;
	unsigned long flags;
	int ret;

	sch = private->sch;

	spin_lock_irqsave(sch->lock, flags);
	private->state = VFIO_CCW_STATE_BUSY;

	orb = cp_get_orb(&private->cp, (u32)(addr_t)sch, sch->lpm);

	/* Issue "Start Subchannel" */
	ccode = ssch(sch->schid, orb);

	switch (ccode) {
	case 0:
		/*
		 * Initialize device status information
		 */
		sch->schib.scsw.cmd.actl |= SCSW_ACTL_START_PEND;
		ret = 0;
		break;
	case 1:		/* Status pending */
	case 2:		/* Busy */
		ret = -EBUSY;
		break;
	case 3:		/* Device/path not operational */
	{
		lpm = orb->cmd.lpm;
		if (lpm != 0)
			sch->lpm &= ~lpm;
		else
			sch->lpm = 0;

		if (cio_update_schib(sch))
			ret = -ENODEV;
		else
			ret = sch->lpm ? -EACCES : -ENODEV;
		break;
	}
	default:
		ret = ccode;
	}
	spin_unlock_irqrestore(sch->lock, flags);
	return ret;
}
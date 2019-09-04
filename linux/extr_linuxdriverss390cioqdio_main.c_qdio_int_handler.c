#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct subchannel_id {int /*<<< orphan*/  sch_no; } ;
struct TYPE_7__ {int /*<<< orphan*/  sch_no; } ;
struct TYPE_6__ {int /*<<< orphan*/  qdio_int; } ;
struct qdio_irq {int state; TYPE_2__ schid; TYPE_1__ perf_stat; scalar_t__ perf_stat_enabled; } ;
struct TYPE_8__ {int cstat; int dstat; } ;
struct TYPE_9__ {TYPE_3__ cmd; } ;
struct irb {TYPE_4__ scsw; } ;
struct ccw_device {TYPE_5__* private; } ;
struct TYPE_10__ {int /*<<< orphan*/  wait_q; struct qdio_irq* qdio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_ERROR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct irb*) ; 
#define  QDIO_IRQ_STATE_ACTIVE 132 
#define  QDIO_IRQ_STATE_CLEANUP 131 
 int const QDIO_IRQ_STATE_ERR ; 
#define  QDIO_IRQ_STATE_ESTABLISHED 130 
#define  QDIO_IRQ_STATE_INACTIVE 129 
#define  QDIO_IRQ_STATE_STOPPED 128 
 int SCHN_STAT_PCI ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ccw_device_get_schid (struct ccw_device*,struct subchannel_id*) ; 
 int /*<<< orphan*/  qdio_establish_handle_irq (struct ccw_device*,int,int) ; 
 int /*<<< orphan*/  qdio_handle_activate_check (struct ccw_device*,unsigned long,int,int) ; 
 int /*<<< orphan*/  qdio_int_handler_pci (struct qdio_irq*) ; 
 int /*<<< orphan*/  qdio_irq_check_sense (struct qdio_irq*,struct irb*) ; 
 int /*<<< orphan*/  qdio_set_state (struct qdio_irq*,int const) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void qdio_int_handler(struct ccw_device *cdev, unsigned long intparm,
		      struct irb *irb)
{
	struct qdio_irq *irq_ptr = cdev->private->qdio_data;
	struct subchannel_id schid;
	int cstat, dstat;

	if (!intparm || !irq_ptr) {
		ccw_device_get_schid(cdev, &schid);
		DBF_ERROR("qint:%4x", schid.sch_no);
		return;
	}

	if (irq_ptr->perf_stat_enabled)
		irq_ptr->perf_stat.qdio_int++;

	if (IS_ERR(irb)) {
		DBF_ERROR("%4x IO error", irq_ptr->schid.sch_no);
		qdio_set_state(irq_ptr, QDIO_IRQ_STATE_ERR);
		wake_up(&cdev->private->wait_q);
		return;
	}
	qdio_irq_check_sense(irq_ptr, irb);
	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;

	switch (irq_ptr->state) {
	case QDIO_IRQ_STATE_INACTIVE:
		qdio_establish_handle_irq(cdev, cstat, dstat);
		break;
	case QDIO_IRQ_STATE_CLEANUP:
		qdio_set_state(irq_ptr, QDIO_IRQ_STATE_INACTIVE);
		break;
	case QDIO_IRQ_STATE_ESTABLISHED:
	case QDIO_IRQ_STATE_ACTIVE:
		if (cstat & SCHN_STAT_PCI) {
			qdio_int_handler_pci(irq_ptr);
			return;
		}
		if (cstat || dstat)
			qdio_handle_activate_check(cdev, intparm, cstat,
						   dstat);
		break;
	case QDIO_IRQ_STATE_STOPPED:
		break;
	default:
		WARN_ON_ONCE(1);
	}
	wake_up(&cdev->private->wait_q);
}
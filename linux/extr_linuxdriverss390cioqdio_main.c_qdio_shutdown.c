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
struct subchannel_id {int /*<<< orphan*/  sch_no; } ;
struct TYPE_3__ {int sch_no; } ;
struct qdio_irq {scalar_t__ state; int /*<<< orphan*/  setup_mutex; scalar_t__ orig_handler; TYPE_1__ schid; } ;
struct ccw_device {TYPE_2__* private; scalar_t__ handler; } ;
struct TYPE_4__ {scalar_t__ intparm; int /*<<< orphan*/  wait_q; struct qdio_irq* qdio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_ERROR (char*,int) ; 
 int /*<<< orphan*/  DBF_EVENT (char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int HZ ; 
 int /*<<< orphan*/  QDIO_DOING_CLEANUP ; 
 int QDIO_FLAG_CLEANUP_USING_CLEAR ; 
 scalar_t__ QDIO_IRQ_STATE_CLEANUP ; 
 scalar_t__ QDIO_IRQ_STATE_ERR ; 
 scalar_t__ QDIO_IRQ_STATE_INACTIVE ; 
 scalar_t__ QDIO_IRQ_STATE_STOPPED ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int ccw_device_clear (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccw_device_get_schid (struct ccw_device*,struct subchannel_id*) ; 
 int ccw_device_halt (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ qdio_int_handler ; 
 int /*<<< orphan*/  qdio_set_state (struct qdio_irq*,scalar_t__) ; 
 int /*<<< orphan*/  qdio_shutdown_debug_entries (struct qdio_irq*) ; 
 int /*<<< orphan*/  qdio_shutdown_queues (struct ccw_device*) ; 
 int /*<<< orphan*/  qdio_shutdown_thinint (struct qdio_irq*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tiqdio_remove_input_queues (struct qdio_irq*) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int) ; 

int qdio_shutdown(struct ccw_device *cdev, int how)
{
	struct qdio_irq *irq_ptr = cdev->private->qdio_data;
	struct subchannel_id schid;
	int rc;

	if (!irq_ptr)
		return -ENODEV;

	WARN_ON_ONCE(irqs_disabled());
	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qshutdown:%4x", schid.sch_no);

	mutex_lock(&irq_ptr->setup_mutex);
	/*
	 * Subchannel was already shot down. We cannot prevent being called
	 * twice since cio may trigger a shutdown asynchronously.
	 */
	if (irq_ptr->state == QDIO_IRQ_STATE_INACTIVE) {
		mutex_unlock(&irq_ptr->setup_mutex);
		return 0;
	}

	/*
	 * Indicate that the device is going down. Scheduling the queue
	 * tasklets is forbidden from here on.
	 */
	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_STOPPED);

	tiqdio_remove_input_queues(irq_ptr);
	qdio_shutdown_queues(cdev);
	qdio_shutdown_debug_entries(irq_ptr);

	/* cleanup subchannel */
	spin_lock_irq(get_ccwdev_lock(cdev));

	if (how & QDIO_FLAG_CLEANUP_USING_CLEAR)
		rc = ccw_device_clear(cdev, QDIO_DOING_CLEANUP);
	else
		/* default behaviour is halt */
		rc = ccw_device_halt(cdev, QDIO_DOING_CLEANUP);
	if (rc) {
		DBF_ERROR("%4x SHUTD ERR", irq_ptr->schid.sch_no);
		DBF_ERROR("rc:%4d", rc);
		goto no_cleanup;
	}

	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_CLEANUP);
	spin_unlock_irq(get_ccwdev_lock(cdev));
	wait_event_interruptible_timeout(cdev->private->wait_q,
		irq_ptr->state == QDIO_IRQ_STATE_INACTIVE ||
		irq_ptr->state == QDIO_IRQ_STATE_ERR,
		10 * HZ);
	spin_lock_irq(get_ccwdev_lock(cdev));

no_cleanup:
	qdio_shutdown_thinint(irq_ptr);

	/* restore interrupt handler */
	if ((void *)cdev->handler == (void *)qdio_int_handler) {
		cdev->handler = irq_ptr->orig_handler;
		cdev->private->intparm = 0;
	}
	spin_unlock_irq(get_ccwdev_lock(cdev));

	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_INACTIVE);
	mutex_unlock(&irq_ptr->setup_mutex);
	if (rc)
		return rc;
	return 0;
}
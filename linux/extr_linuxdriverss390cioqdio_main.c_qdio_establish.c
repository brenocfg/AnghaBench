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
typedef  scalar_t__ u32 ;
struct subchannel_id {int /*<<< orphan*/  sch_no; } ;
struct TYPE_6__ {int sch_no; } ;
struct TYPE_8__ {scalar_t__ cda; int /*<<< orphan*/  count; int /*<<< orphan*/  flags; int /*<<< orphan*/  cmd_code; } ;
struct TYPE_5__ {int /*<<< orphan*/  count; int /*<<< orphan*/  cmd; } ;
struct qdio_irq {scalar_t__ state; int /*<<< orphan*/  setup_mutex; TYPE_2__ schid; TYPE_4__ ccw; scalar_t__ qdr; TYPE_1__ equeue; } ;
struct qdio_initialize {struct ccw_device* cdev; } ;
struct ccw_device {TYPE_3__* private; } ;
typedef  scalar_t__ addr_t ;
struct TYPE_7__ {int /*<<< orphan*/  wait_q; struct qdio_irq* qdio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_FLAG_SLI ; 
 int /*<<< orphan*/  DBF_ERROR (char*,int) ; 
 int /*<<< orphan*/  DBF_EVENT (char*,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  QDIO_DOING_ESTABLISH ; 
 int /*<<< orphan*/  QDIO_FLAG_CLEANUP_USING_CLEAR ; 
 scalar_t__ QDIO_IRQ_STATE_ERR ; 
 scalar_t__ QDIO_IRQ_STATE_ESTABLISHED ; 
 int /*<<< orphan*/  ccw_device_get_schid (struct ccw_device*,struct subchannel_id*) ; 
 int /*<<< orphan*/  ccw_device_set_options_mask (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int ccw_device_start (struct ccw_device*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdio_detect_hsicq (struct qdio_irq*) ; 
 int qdio_establish_thinint (struct qdio_irq*) ; 
 int /*<<< orphan*/  qdio_init_buf_states (struct qdio_irq*) ; 
 int /*<<< orphan*/  qdio_print_subchannel_info (struct qdio_irq*,struct ccw_device*) ; 
 int /*<<< orphan*/  qdio_setup_debug_entries (struct qdio_irq*,struct ccw_device*) ; 
 int /*<<< orphan*/  qdio_setup_irq (struct qdio_initialize*) ; 
 int /*<<< orphan*/  qdio_setup_ssqd_info (struct qdio_irq*) ; 
 int /*<<< orphan*/  qdio_shutdown (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event_interruptible_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int qdio_establish(struct qdio_initialize *init_data)
{
	struct ccw_device *cdev = init_data->cdev;
	struct subchannel_id schid;
	struct qdio_irq *irq_ptr;
	int rc;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qestablish:%4x", schid.sch_no);

	irq_ptr = cdev->private->qdio_data;
	if (!irq_ptr)
		return -ENODEV;

	mutex_lock(&irq_ptr->setup_mutex);
	qdio_setup_irq(init_data);

	rc = qdio_establish_thinint(irq_ptr);
	if (rc) {
		mutex_unlock(&irq_ptr->setup_mutex);
		qdio_shutdown(cdev, QDIO_FLAG_CLEANUP_USING_CLEAR);
		return rc;
	}

	/* establish q */
	irq_ptr->ccw.cmd_code = irq_ptr->equeue.cmd;
	irq_ptr->ccw.flags = CCW_FLAG_SLI;
	irq_ptr->ccw.count = irq_ptr->equeue.count;
	irq_ptr->ccw.cda = (u32)((addr_t)irq_ptr->qdr);

	spin_lock_irq(get_ccwdev_lock(cdev));
	ccw_device_set_options_mask(cdev, 0);

	rc = ccw_device_start(cdev, &irq_ptr->ccw, QDIO_DOING_ESTABLISH, 0, 0);
	spin_unlock_irq(get_ccwdev_lock(cdev));
	if (rc) {
		DBF_ERROR("%4x est IO ERR", irq_ptr->schid.sch_no);
		DBF_ERROR("rc:%4x", rc);
		mutex_unlock(&irq_ptr->setup_mutex);
		qdio_shutdown(cdev, QDIO_FLAG_CLEANUP_USING_CLEAR);
		return rc;
	}

	wait_event_interruptible_timeout(cdev->private->wait_q,
		irq_ptr->state == QDIO_IRQ_STATE_ESTABLISHED ||
		irq_ptr->state == QDIO_IRQ_STATE_ERR, HZ);

	if (irq_ptr->state != QDIO_IRQ_STATE_ESTABLISHED) {
		mutex_unlock(&irq_ptr->setup_mutex);
		qdio_shutdown(cdev, QDIO_FLAG_CLEANUP_USING_CLEAR);
		return -EIO;
	}

	qdio_setup_ssqd_info(irq_ptr);

	qdio_detect_hsicq(irq_ptr);

	/* qebsm is now setup if available, initialize buffer states */
	qdio_init_buf_states(irq_ptr);

	mutex_unlock(&irq_ptr->setup_mutex);
	qdio_print_subchannel_info(irq_ptr, cdev);
	qdio_setup_debug_entries(irq_ptr, cdev);
	return 0;
}
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
struct TYPE_4__ {int /*<<< orphan*/  sch_no; } ;
struct qdio_irq {TYPE_2__ schid; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_3__ {struct qdio_irq* qdio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct qdio_irq*,char*) ; 
 int /*<<< orphan*/  DBF_ERROR (char*,int,...) ; 
 int /*<<< orphan*/  DBF_INFO ; 
 int DEV_STAT_CHN_END ; 
 int DEV_STAT_DEV_END ; 
 int /*<<< orphan*/  QDIO_IRQ_STATE_ERR ; 
 int /*<<< orphan*/  QDIO_IRQ_STATE_ESTABLISHED ; 
 int /*<<< orphan*/  qdio_set_state (struct qdio_irq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qdio_establish_handle_irq(struct ccw_device *cdev, int cstat,
				      int dstat)
{
	struct qdio_irq *irq_ptr = cdev->private->qdio_data;

	DBF_DEV_EVENT(DBF_INFO, irq_ptr, "qest irq");

	if (cstat)
		goto error;
	if (dstat & ~(DEV_STAT_DEV_END | DEV_STAT_CHN_END))
		goto error;
	if (!(dstat & DEV_STAT_DEV_END))
		goto error;
	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_ESTABLISHED);
	return;

error:
	DBF_ERROR("%4x EQ:error", irq_ptr->schid.sch_no);
	DBF_ERROR("ds: %2x cs:%2x", dstat, cstat);
	qdio_set_state(irq_ptr, QDIO_IRQ_STATE_ERR);
}
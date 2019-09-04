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
struct subchannel_id {int /*<<< orphan*/  sch_no; } ;
struct qdio_irq {int /*<<< orphan*/  setup_mutex; int /*<<< orphan*/ * debug_area; } ;
struct ccw_device {TYPE_1__* private; } ;
struct TYPE_2__ {struct qdio_irq* qdio_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct qdio_irq*,char*) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int /*<<< orphan*/  DBF_EVENT (char*,int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  ccw_device_get_schid (struct ccw_device*,struct subchannel_id*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdio_release_memory (struct qdio_irq*) ; 

int qdio_free(struct ccw_device *cdev)
{
	struct qdio_irq *irq_ptr = cdev->private->qdio_data;
	struct subchannel_id schid;

	if (!irq_ptr)
		return -ENODEV;

	ccw_device_get_schid(cdev, &schid);
	DBF_EVENT("qfree:%4x", schid.sch_no);
	DBF_DEV_EVENT(DBF_ERR, irq_ptr, "dbf abandoned");
	mutex_lock(&irq_ptr->setup_mutex);

	irq_ptr->debug_area = NULL;
	cdev->private->qdio_data = NULL;
	mutex_unlock(&irq_ptr->setup_mutex);

	qdio_release_memory(irq_ptr);
	return 0;
}
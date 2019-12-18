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
struct iucv_irq_list {int /*<<< orphan*/  list; int /*<<< orphan*/  data; } ;
struct iucv_irq_data {scalar_t__ ippathid; int iptype; } ;
struct ext_code {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IRQEXT_IUC ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  inc_irq_stat (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_error_no_listener ; 
 struct iucv_irq_data** iucv_irq_data ; 
 scalar_t__ iucv_max_pathid ; 
 int /*<<< orphan*/  iucv_queue_lock ; 
 int /*<<< orphan*/  iucv_sever_pathid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iucv_task_queue ; 
 int /*<<< orphan*/  iucv_tasklet ; 
 int /*<<< orphan*/  iucv_work ; 
 int /*<<< orphan*/  iucv_work_queue ; 
 struct iucv_irq_list* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct iucv_irq_data*,int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iucv_external_interrupt(struct ext_code ext_code,
				    unsigned int param32, unsigned long param64)
{
	struct iucv_irq_data *p;
	struct iucv_irq_list *work;

	inc_irq_stat(IRQEXT_IUC);
	p = iucv_irq_data[smp_processor_id()];
	if (p->ippathid >= iucv_max_pathid) {
		WARN_ON(p->ippathid >= iucv_max_pathid);
		iucv_sever_pathid(p->ippathid, iucv_error_no_listener);
		return;
	}
	BUG_ON(p->iptype  < 0x01 || p->iptype > 0x09);
	work = kmalloc(sizeof(struct iucv_irq_list), GFP_ATOMIC);
	if (!work) {
		pr_warn("iucv_external_interrupt: out of memory\n");
		return;
	}
	memcpy(&work->data, p, sizeof(work->data));
	spin_lock(&iucv_queue_lock);
	if (p->iptype == 0x01) {
		/* Path pending interrupt. */
		list_add_tail(&work->list, &iucv_work_queue);
		schedule_work(&iucv_work);
	} else {
		/* The other interrupts. */
		list_add_tail(&work->list, &iucv_task_queue);
		tasklet_schedule(&iucv_tasklet);
	}
	spin_unlock(&iucv_queue_lock);
}
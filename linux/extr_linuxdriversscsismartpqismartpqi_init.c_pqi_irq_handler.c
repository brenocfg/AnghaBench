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
struct pqi_queue_group {struct pqi_ctrl_info* ctrl_info; } ;
struct pqi_ctrl_info {int event_irq; int /*<<< orphan*/  num_interrupts; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AIO_PATH ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  RAID_PATH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pqi_is_valid_irq (struct pqi_ctrl_info*) ; 
 scalar_t__ pqi_process_event_intr (struct pqi_ctrl_info*) ; 
 unsigned int pqi_process_io_intr (struct pqi_ctrl_info*,struct pqi_queue_group*) ; 
 int /*<<< orphan*/  pqi_start_io (struct pqi_ctrl_info*,struct pqi_queue_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pqi_irq_handler(int irq, void *data)
{
	struct pqi_ctrl_info *ctrl_info;
	struct pqi_queue_group *queue_group;
	unsigned int num_responses_handled;

	queue_group = data;
	ctrl_info = queue_group->ctrl_info;

	if (!pqi_is_valid_irq(ctrl_info))
		return IRQ_NONE;

	num_responses_handled = pqi_process_io_intr(ctrl_info, queue_group);

	if (irq == ctrl_info->event_irq)
		num_responses_handled += pqi_process_event_intr(ctrl_info);

	if (num_responses_handled)
		atomic_inc(&ctrl_info->num_interrupts);

	pqi_start_io(ctrl_info, queue_group, RAID_PATH, NULL);
	pqi_start_io(ctrl_info, queue_group, AIO_PATH, NULL);

	return IRQ_HANDLED;
}
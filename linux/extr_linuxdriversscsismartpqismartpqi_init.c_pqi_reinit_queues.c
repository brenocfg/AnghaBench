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
struct pqi_event_queue {scalar_t__ oq_ci_copy; int /*<<< orphan*/  oq_pi; } ;
struct pqi_admin_queues {int /*<<< orphan*/  oq_pi; scalar_t__ oq_ci_copy; scalar_t__ iq_pi_copy; } ;
struct pqi_ctrl_info {unsigned int num_queue_groups; struct pqi_event_queue event_queue; TYPE_1__* queue_groups; struct pqi_admin_queues admin_queues; } ;
struct TYPE_2__ {int /*<<< orphan*/  oq_pi; int /*<<< orphan*/ * iq_ci; scalar_t__ oq_ci_copy; scalar_t__* iq_pi_copy; } ;

/* Variables and functions */
 size_t AIO_PATH ; 
 size_t RAID_PATH ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pqi_reinit_queues(struct pqi_ctrl_info *ctrl_info)
{
	unsigned int i;
	struct pqi_admin_queues *admin_queues;
	struct pqi_event_queue *event_queue;

	admin_queues = &ctrl_info->admin_queues;
	admin_queues->iq_pi_copy = 0;
	admin_queues->oq_ci_copy = 0;
	writel(0, admin_queues->oq_pi);

	for (i = 0; i < ctrl_info->num_queue_groups; i++) {
		ctrl_info->queue_groups[i].iq_pi_copy[RAID_PATH] = 0;
		ctrl_info->queue_groups[i].iq_pi_copy[AIO_PATH] = 0;
		ctrl_info->queue_groups[i].oq_ci_copy = 0;

		writel(0, ctrl_info->queue_groups[i].iq_ci[RAID_PATH]);
		writel(0, ctrl_info->queue_groups[i].iq_ci[AIO_PATH]);
		writel(0, ctrl_info->queue_groups[i].oq_pi);
	}

	event_queue = &ctrl_info->event_queue;
	writel(0, event_queue->oq_pi);
	event_queue->oq_ci_copy = 0;
}
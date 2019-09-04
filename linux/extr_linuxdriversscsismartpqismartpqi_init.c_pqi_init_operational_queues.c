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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {scalar_t__ int_msg_num; scalar_t__ oq_id; } ;
struct pqi_ctrl_info {unsigned int num_queue_groups; TYPE_2__* queue_groups; TYPE_1__ event_queue; } ;
struct TYPE_4__ {unsigned int int_msg_num; int /*<<< orphan*/ * request_list; int /*<<< orphan*/ * submit_lock; scalar_t__ oq_id; scalar_t__* iq_id; struct pqi_ctrl_info* ctrl_info; } ;

/* Variables and functions */
 size_t AIO_PATH ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PQI_MIN_OPERATIONAL_QUEUE_ID ; 
 size_t RAID_PATH ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pqi_init_operational_queues(struct pqi_ctrl_info *ctrl_info)
{
	unsigned int i;
	u16 next_iq_id = PQI_MIN_OPERATIONAL_QUEUE_ID;
	u16 next_oq_id = PQI_MIN_OPERATIONAL_QUEUE_ID;

	/*
	 * Initialize the backpointers to the controller structure in
	 * each operational queue group structure.
	 */
	for (i = 0; i < ctrl_info->num_queue_groups; i++)
		ctrl_info->queue_groups[i].ctrl_info = ctrl_info;

	/*
	 * Assign IDs to all operational queues.  Note that the IDs
	 * assigned to operational IQs are independent of the IDs
	 * assigned to operational OQs.
	 */
	ctrl_info->event_queue.oq_id = next_oq_id++;
	for (i = 0; i < ctrl_info->num_queue_groups; i++) {
		ctrl_info->queue_groups[i].iq_id[RAID_PATH] = next_iq_id++;
		ctrl_info->queue_groups[i].iq_id[AIO_PATH] = next_iq_id++;
		ctrl_info->queue_groups[i].oq_id = next_oq_id++;
	}

	/*
	 * Assign MSI-X table entry indexes to all queues.  Note that the
	 * interrupt for the event queue is shared with the first queue group.
	 */
	ctrl_info->event_queue.int_msg_num = 0;
	for (i = 0; i < ctrl_info->num_queue_groups; i++)
		ctrl_info->queue_groups[i].int_msg_num = i;

	for (i = 0; i < ctrl_info->num_queue_groups; i++) {
		spin_lock_init(&ctrl_info->queue_groups[i].submit_lock[0]);
		spin_lock_init(&ctrl_info->queue_groups[i].submit_lock[1]);
		INIT_LIST_HEAD(&ctrl_info->queue_groups[i].request_list[0]);
		INIT_LIST_HEAD(&ctrl_info->queue_groups[i].request_list[1]);
	}
}
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
struct TYPE_2__ {scalar_t__ expires; } ;
struct pqi_ctrl_info {TYPE_1__ heartbeat_timer; int /*<<< orphan*/  previous_heartbeat_count; int /*<<< orphan*/  num_interrupts; int /*<<< orphan*/  previous_num_interrupts; int /*<<< orphan*/  heartbeat_counter; } ;

/* Variables and functions */
 scalar_t__ PQI_HEARTBEAT_TIMER_INTERVAL ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  pqi_read_heartbeat_counter (struct pqi_ctrl_info*) ; 

__attribute__((used)) static void pqi_start_heartbeat_timer(struct pqi_ctrl_info *ctrl_info)
{
	if (!ctrl_info->heartbeat_counter)
		return;

	ctrl_info->previous_num_interrupts =
		atomic_read(&ctrl_info->num_interrupts);
	ctrl_info->previous_heartbeat_count =
		pqi_read_heartbeat_counter(ctrl_info);

	ctrl_info->heartbeat_timer.expires =
		jiffies + PQI_HEARTBEAT_TIMER_INTERVAL;
	add_timer(&ctrl_info->heartbeat_timer);
}
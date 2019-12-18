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
struct tep_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sched_switch_handler ; 
 int /*<<< orphan*/  sched_wakeup_handler ; 
 int /*<<< orphan*/  tep_unregister_event_handler (struct tep_handle*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void TEP_PLUGIN_UNLOADER(struct tep_handle *tep)
{
	tep_unregister_event_handler(tep, -1, "sched", "sched_switch",
				     sched_switch_handler, NULL);

	tep_unregister_event_handler(tep, -1, "sched", "sched_wakeup",
				     sched_wakeup_handler, NULL);

	tep_unregister_event_handler(tep, -1, "sched", "sched_wakeup_new",
				     sched_wakeup_handler, NULL);
}
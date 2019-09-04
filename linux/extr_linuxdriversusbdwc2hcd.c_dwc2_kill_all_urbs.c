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
struct dwc2_hsotg {int /*<<< orphan*/  periodic_sched_queued; int /*<<< orphan*/  periodic_sched_assigned; int /*<<< orphan*/  periodic_sched_ready; int /*<<< orphan*/  periodic_sched_inactive; int /*<<< orphan*/  non_periodic_sched_active; int /*<<< orphan*/  non_periodic_sched_waiting; int /*<<< orphan*/  non_periodic_sched_inactive; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwc2_kill_urbs_in_qh_list (struct dwc2_hsotg*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc2_kill_all_urbs(struct dwc2_hsotg *hsotg)
{
	dwc2_kill_urbs_in_qh_list(hsotg, &hsotg->non_periodic_sched_inactive);
	dwc2_kill_urbs_in_qh_list(hsotg, &hsotg->non_periodic_sched_waiting);
	dwc2_kill_urbs_in_qh_list(hsotg, &hsotg->non_periodic_sched_active);
	dwc2_kill_urbs_in_qh_list(hsotg, &hsotg->periodic_sched_inactive);
	dwc2_kill_urbs_in_qh_list(hsotg, &hsotg->periodic_sched_ready);
	dwc2_kill_urbs_in_qh_list(hsotg, &hsotg->periodic_sched_assigned);
	dwc2_kill_urbs_in_qh_list(hsotg, &hsotg->periodic_sched_queued);
}
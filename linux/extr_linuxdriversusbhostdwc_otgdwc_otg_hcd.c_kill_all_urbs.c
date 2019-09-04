#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  periodic_sched_queued; int /*<<< orphan*/  periodic_sched_assigned; int /*<<< orphan*/  periodic_sched_ready; int /*<<< orphan*/  periodic_sched_inactive; int /*<<< orphan*/  non_periodic_sched_active; int /*<<< orphan*/  non_periodic_sched_inactive; } ;
typedef  TYPE_1__ dwc_otg_hcd_t ;

/* Variables and functions */
 int /*<<< orphan*/  kill_urbs_in_qh_list (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kill_all_urbs(dwc_otg_hcd_t * hcd)
{
	kill_urbs_in_qh_list(hcd, &hcd->non_periodic_sched_inactive);
	kill_urbs_in_qh_list(hcd, &hcd->non_periodic_sched_active);
	kill_urbs_in_qh_list(hcd, &hcd->periodic_sched_inactive);
	kill_urbs_in_qh_list(hcd, &hcd->periodic_sched_ready);
	kill_urbs_in_qh_list(hcd, &hcd->periodic_sched_assigned);
	kill_urbs_in_qh_list(hcd, &hcd->periodic_sched_queued);
}
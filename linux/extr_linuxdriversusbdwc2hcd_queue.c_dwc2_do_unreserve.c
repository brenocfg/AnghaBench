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
struct dwc2_qh {int unreserve_pending; scalar_t__ host_us; int /*<<< orphan*/  qh_list_entry; } ;
struct TYPE_2__ {scalar_t__ uframe_sched; } ;
struct dwc2_hsotg {int /*<<< orphan*/  periodic_channels; TYPE_1__ params; int /*<<< orphan*/  periodic_usecs; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dwc2_uframe_unschedule (struct dwc2_hsotg*,struct dwc2_qh*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dwc2_do_unreserve(struct dwc2_hsotg *hsotg, struct dwc2_qh *qh)
{
	assert_spin_locked(&hsotg->lock);

	WARN_ON(!qh->unreserve_pending);

	/* No more unreserve pending--we're doing it */
	qh->unreserve_pending = false;

	if (WARN_ON(!list_empty(&qh->qh_list_entry)))
		list_del_init(&qh->qh_list_entry);

	/* Update claimed usecs per (micro)frame */
	hsotg->periodic_usecs -= qh->host_us;

	if (hsotg->params.uframe_sched) {
		dwc2_uframe_unschedule(hsotg, qh);
	} else {
		/* Release periodic channel reservation */
		hsotg->periodic_channels--;
	}
}
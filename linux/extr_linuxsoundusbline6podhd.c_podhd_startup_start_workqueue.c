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
struct usb_line6_podhd {int /*<<< orphan*/  startup_work; int /*<<< orphan*/  startup_progress; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STARTUP_PROGRESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PODHD_STARTUP_SCHEDULE_WORKQUEUE ; 
 struct usb_line6_podhd* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct usb_line6_podhd* pod ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  startup_timer ; 

__attribute__((used)) static void podhd_startup_start_workqueue(struct timer_list *t)
{
	struct usb_line6_podhd *pod = from_timer(pod, t, startup_timer);

	CHECK_STARTUP_PROGRESS(pod->startup_progress,
		PODHD_STARTUP_SCHEDULE_WORKQUEUE);

	/* schedule work for global work queue: */
	schedule_work(&pod->startup_work);
}
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
struct usb_line6_variax {int /*<<< orphan*/  startup_work; int /*<<< orphan*/  startup_progress; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STARTUP_PROGRESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARIAX_STARTUP_WORKQUEUE ; 
 struct usb_line6_variax* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  startup_timer2 ; 
 struct usb_line6_variax* variax ; 

__attribute__((used)) static void variax_startup5(struct timer_list *t)
{
	struct usb_line6_variax *variax = from_timer(variax, t, startup_timer2);

	CHECK_STARTUP_PROGRESS(variax->startup_progress,
			       VARIAX_STARTUP_WORKQUEUE);

	/* schedule work for global work queue: */
	schedule_work(&variax->startup_work);
}
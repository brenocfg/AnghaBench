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
struct usb_line6_pod {int /*<<< orphan*/  startup_work; int /*<<< orphan*/  startup_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STARTUP_PROGRESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POD_STARTUP_WORKQUEUE ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pod_startup3(struct usb_line6_pod *pod)
{
	CHECK_STARTUP_PROGRESS(pod->startup_progress, POD_STARTUP_WORKQUEUE);

	/* schedule work for global work queue: */
	schedule_work(&pod->startup_work);
}
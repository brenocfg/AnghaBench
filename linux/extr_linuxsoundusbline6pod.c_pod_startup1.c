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
struct usb_line6_pod {int /*<<< orphan*/  startup_timer; int /*<<< orphan*/  startup_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STARTUP_PROGRESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POD_STARTUP_DELAY ; 
 int /*<<< orphan*/  POD_STARTUP_INIT ; 
 int /*<<< orphan*/  line6_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pod_startup2 ; 

__attribute__((used)) static void pod_startup1(struct usb_line6_pod *pod)
{
	CHECK_STARTUP_PROGRESS(pod->startup_progress, POD_STARTUP_INIT);

	/* delay startup procedure: */
	line6_start_timer(&pod->startup_timer, POD_STARTUP_DELAY, pod_startup2);
}
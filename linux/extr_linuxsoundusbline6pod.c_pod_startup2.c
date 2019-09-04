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
struct usb_line6 {int dummy; } ;
struct usb_line6_pod {int /*<<< orphan*/  startup_progress; struct usb_line6 line6; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STARTUP_PROGRESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POD_STARTUP_VERSIONREQ ; 
 struct usb_line6_pod* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line6_version_request_async (struct usb_line6*) ; 
 struct usb_line6_pod* pod ; 
 int /*<<< orphan*/  startup_timer ; 

__attribute__((used)) static void pod_startup2(struct timer_list *t)
{
	struct usb_line6_pod *pod = from_timer(pod, t, startup_timer);
	struct usb_line6 *line6 = &pod->line6;

	CHECK_STARTUP_PROGRESS(pod->startup_progress, POD_STARTUP_VERSIONREQ);

	/* request firmware version: */
	line6_version_request_async(line6);
}
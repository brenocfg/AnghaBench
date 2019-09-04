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
struct usb_line6_variax {scalar_t__ startup_progress; int /*<<< orphan*/  startup_timer1; struct usb_line6 line6; } ;
struct timer_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VARIAX_STARTUP_DELAY1 ; 
 scalar_t__ VARIAX_STARTUP_LAST ; 
 scalar_t__ VARIAX_STARTUP_VERSIONREQ ; 
 struct usb_line6_variax* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  line6_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (struct timer_list*)) ; 
 int /*<<< orphan*/  line6_version_request_async (struct usb_line6*) ; 
 int /*<<< orphan*/  startup_timer1 ; 
 struct usb_line6_variax* variax ; 

__attribute__((used)) static void variax_startup2(struct timer_list *t)
{
	struct usb_line6_variax *variax = from_timer(variax, t, startup_timer1);
	struct usb_line6 *line6 = &variax->line6;

	/* schedule another startup procedure until startup is complete: */
	if (variax->startup_progress >= VARIAX_STARTUP_LAST)
		return;

	variax->startup_progress = VARIAX_STARTUP_VERSIONREQ;
	line6_start_timer(&variax->startup_timer1, VARIAX_STARTUP_DELAY1,
			  variax_startup2);

	/* request firmware version: */
	line6_version_request_async(line6);
}
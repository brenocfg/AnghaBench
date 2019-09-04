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
struct usb_line6_variax {int /*<<< orphan*/  startup_timer2; int /*<<< orphan*/  startup_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STARTUP_PROGRESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARIAX_STARTUP_DELAY3 ; 
 int /*<<< orphan*/  VARIAX_STARTUP_WAIT ; 
 int /*<<< orphan*/  line6_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  variax_startup4 ; 

__attribute__((used)) static void variax_startup3(struct usb_line6_variax *variax)
{
	CHECK_STARTUP_PROGRESS(variax->startup_progress, VARIAX_STARTUP_WAIT);

	/* delay startup procedure: */
	line6_start_timer(&variax->startup_timer2, VARIAX_STARTUP_DELAY3,
			  variax_startup4);
}
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
struct usb_line6_variax {int /*<<< orphan*/  startup_timer1; int /*<<< orphan*/  startup_progress; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_STARTUP_PROGRESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VARIAX_STARTUP_DELAY1 ; 
 int /*<<< orphan*/  VARIAX_STARTUP_INIT ; 
 int /*<<< orphan*/  line6_start_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  variax_startup2 ; 

__attribute__((used)) static void variax_startup1(struct usb_line6_variax *variax)
{
	CHECK_STARTUP_PROGRESS(variax->startup_progress, VARIAX_STARTUP_INIT);

	/* delay startup procedure: */
	line6_start_timer(&variax->startup_timer1, VARIAX_STARTUP_DELAY1,
			  variax_startup2);
}
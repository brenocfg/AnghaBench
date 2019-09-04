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
struct usb_line6_variax {int /*<<< orphan*/  buffer_activate; int /*<<< orphan*/  startup_work; int /*<<< orphan*/  startup_timer2; int /*<<< orphan*/  startup_timer1; } ;
struct usb_line6 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void line6_variax_disconnect(struct usb_line6 *line6)
{
	struct usb_line6_variax *variax = (struct usb_line6_variax *)line6;

	del_timer(&variax->startup_timer1);
	del_timer(&variax->startup_timer2);
	cancel_work_sync(&variax->startup_work);

	kfree(variax->buffer_activate);
}
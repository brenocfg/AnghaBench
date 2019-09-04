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
struct usb_anchor {int /*<<< orphan*/  wait; int /*<<< orphan*/  suspend_wakeups; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_anchor_check_wakeup (struct usb_anchor*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void usb_anchor_resume_wakeups(struct usb_anchor *anchor)
{
	if (!anchor)
		return;

	atomic_dec(&anchor->suspend_wakeups);
	if (usb_anchor_check_wakeup(anchor))
		wake_up(&anchor->wait);
}
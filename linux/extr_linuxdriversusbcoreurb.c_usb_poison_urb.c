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
struct urb {int /*<<< orphan*/  use_count; int /*<<< orphan*/  ep; int /*<<< orphan*/  dev; int /*<<< orphan*/  reject; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  usb_hcd_unlink_urb (struct urb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb_queue ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void usb_poison_urb(struct urb *urb)
{
	might_sleep();
	if (!urb)
		return;
	atomic_inc(&urb->reject);

	if (!urb->dev || !urb->ep)
		return;

	usb_hcd_unlink_urb(urb, -ENOENT);
	wait_event(usb_kill_urb_queue, atomic_read(&urb->use_count) == 0);
}
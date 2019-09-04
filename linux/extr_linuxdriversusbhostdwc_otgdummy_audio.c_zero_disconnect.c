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
struct zero_dev {int /*<<< orphan*/  lock; } ;
struct usb_gadget {int dummy; } ;

/* Variables and functions */
 struct zero_dev* get_gadget_data (struct usb_gadget*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zero_reset_config (struct zero_dev*) ; 

__attribute__((used)) static void
zero_disconnect (struct usb_gadget *gadget)
{
	struct zero_dev		*dev = get_gadget_data (gadget);
	unsigned long		flags;

	spin_lock_irqsave (&dev->lock, flags);
	zero_reset_config (dev);

	/* a more significant application might have some non-usb
	 * activities to quiesce here, saving resources like power
	 * or pushing the notification up a network stack.
	 */
	spin_unlock_irqrestore (&dev->lock, flags);

	/* next we may get setup() calls to enumerate new connections;
	 * or an unbind() during shutdown (including removing module).
	 */
}
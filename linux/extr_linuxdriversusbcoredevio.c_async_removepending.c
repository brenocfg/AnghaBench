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
struct usb_dev_state {int /*<<< orphan*/  lock; } ;
struct async {int /*<<< orphan*/  asynclist; struct usb_dev_state* ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void async_removepending(struct async *as)
{
	struct usb_dev_state *ps = as->ps;
	unsigned long flags;

	spin_lock_irqsave(&ps->lock, flags);
	list_del_init(&as->asynclist);
	spin_unlock_irqrestore(&ps->lock, flags);
}
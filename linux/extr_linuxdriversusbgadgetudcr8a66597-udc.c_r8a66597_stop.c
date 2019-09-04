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
struct usb_gadget {int dummy; } ;
struct r8a66597 {int /*<<< orphan*/ * driver; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTENB0 ; 
 int /*<<< orphan*/  VBSE ; 
 int /*<<< orphan*/  disable_controller (struct r8a66597*) ; 
 struct r8a66597* gadget_to_r8a66597 (struct usb_gadget*) ; 
 int /*<<< orphan*/  r8a66597_bclr (struct r8a66597*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int r8a66597_stop(struct usb_gadget *gadget)
{
	struct r8a66597 *r8a66597 = gadget_to_r8a66597(gadget);
	unsigned long flags;

	spin_lock_irqsave(&r8a66597->lock, flags);
	r8a66597_bclr(r8a66597, VBSE, INTENB0);
	disable_controller(r8a66597);
	spin_unlock_irqrestore(&r8a66597->lock, flags);

	r8a66597->driver = NULL;
	return 0;
}
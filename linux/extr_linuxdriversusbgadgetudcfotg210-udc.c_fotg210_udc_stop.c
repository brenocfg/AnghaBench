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
struct fotg210_udc {int /*<<< orphan*/  lock; int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  fotg210_init (struct fotg210_udc*) ; 
 struct fotg210_udc* gadget_to_fotg210 (struct usb_gadget*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int fotg210_udc_stop(struct usb_gadget *g)
{
	struct fotg210_udc *fotg210 = gadget_to_fotg210(g);
	unsigned long	flags;

	spin_lock_irqsave(&fotg210->lock, flags);

	fotg210_init(fotg210);
	fotg210->driver = NULL;

	spin_unlock_irqrestore(&fotg210->lock, flags);

	return 0;
}
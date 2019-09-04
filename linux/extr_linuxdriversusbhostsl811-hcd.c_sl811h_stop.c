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
struct usb_hcd {int /*<<< orphan*/  rh_timer; } ;
struct sl811 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct sl811* hcd_to_sl811 (struct usb_hcd*) ; 
 int /*<<< orphan*/  port_power (struct sl811*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
sl811h_stop(struct usb_hcd *hcd)
{
	struct sl811	*sl811 = hcd_to_sl811(hcd);
	unsigned long	flags;

	del_timer_sync(&hcd->rh_timer);

	spin_lock_irqsave(&sl811->lock, flags);
	port_power(sl811, 0);
	spin_unlock_irqrestore(&sl811->lock, flags);
}
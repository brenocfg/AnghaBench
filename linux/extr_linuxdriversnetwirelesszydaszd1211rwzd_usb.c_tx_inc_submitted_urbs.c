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
struct zd_usb_tx {scalar_t__ submitted_urbs; int stopped; int /*<<< orphan*/  lock; } ;
struct zd_usb {struct zd_usb_tx tx; } ;

/* Variables and functions */
 scalar_t__ ZD_USB_TX_HIGH ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zd_usb_to_hw (struct zd_usb*) ; 

__attribute__((used)) static void tx_inc_submitted_urbs(struct zd_usb *usb)
{
	struct zd_usb_tx *tx = &usb->tx;
	unsigned long flags;

	spin_lock_irqsave(&tx->lock, flags);
	++tx->submitted_urbs;
	if (!tx->stopped && tx->submitted_urbs > ZD_USB_TX_HIGH) {
		ieee80211_stop_queues(zd_usb_to_hw(usb));
		tx->stopped = 1;
	}
	spin_unlock_irqrestore(&tx->lock, flags);
}
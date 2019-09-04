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
struct zd_usb_tx {int /*<<< orphan*/  watchdog_work; scalar_t__ watchdog_enabled; scalar_t__ submitted_urbs; int /*<<< orphan*/  submitted; int /*<<< orphan*/  submitted_skbs; scalar_t__ stopped; int /*<<< orphan*/  enabled; int /*<<< orphan*/  lock; } ;
struct zd_usb {struct zd_usb_tx tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_usb_anchor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_tx_watchdog_handler ; 

__attribute__((used)) static inline void init_usb_tx(struct zd_usb *usb)
{
	struct zd_usb_tx *tx = &usb->tx;

	spin_lock_init(&tx->lock);
	atomic_set(&tx->enabled, 0);
	tx->stopped = 0;
	skb_queue_head_init(&tx->submitted_skbs);
	init_usb_anchor(&tx->submitted);
	tx->submitted_urbs = 0;
	tx->watchdog_enabled = 0;
	INIT_DELAYED_WORK(&tx->watchdog_work, zd_tx_watchdog_handler);
}
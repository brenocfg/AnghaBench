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
struct sk_buff {int dummy; } ;
struct b43_wl {int beacon0_uploaded; int beacon1_uploaded; int /*<<< orphan*/  beacon_update_trigger; int /*<<< orphan*/  hw; int /*<<< orphan*/  beacon_lock; struct sk_buff* current_beacon; int /*<<< orphan*/  vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* ieee80211_beacon_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void b43_update_templates(struct b43_wl *wl)
{
	struct sk_buff *beacon, *old_beacon;
	unsigned long flags;

	/* This is the top half of the asynchronous beacon update.
	 * The bottom half is the beacon IRQ.
	 * Beacon update must be asynchronous to avoid sending an
	 * invalid beacon. This can happen for example, if the firmware
	 * transmits a beacon while we are updating it. */

	/* We could modify the existing beacon and set the aid bit in
	 * the TIM field, but that would probably require resizing and
	 * moving of data within the beacon template.
	 * Simply request a new beacon and let mac80211 do the hard work. */
	beacon = ieee80211_beacon_get(wl->hw, wl->vif);
	if (unlikely(!beacon))
		return;

	spin_lock_irqsave(&wl->beacon_lock, flags);
	old_beacon = wl->current_beacon;
	wl->current_beacon = beacon;
	wl->beacon0_uploaded = false;
	wl->beacon1_uploaded = false;
	spin_unlock_irqrestore(&wl->beacon_lock, flags);

	ieee80211_queue_work(wl->hw, &wl->beacon_update_trigger);

	if (old_beacon)
		dev_kfree_skb_any(old_beacon);
}
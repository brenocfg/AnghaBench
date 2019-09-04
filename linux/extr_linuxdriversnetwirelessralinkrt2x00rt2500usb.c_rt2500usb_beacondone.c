#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct urb {scalar_t__ context; } ;
struct queue_entry_priv_usb_bcn {struct urb* urb; struct urb* guardian_urb; } ;
struct queue_entry {int /*<<< orphan*/ * skb; TYPE_2__* queue; struct queue_entry_priv_usb_bcn* priv_data; } ;
struct TYPE_4__ {TYPE_1__* rt2x00dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_ENABLED_RADIO ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2500usb_beacondone(struct urb *urb)
{
	struct queue_entry *entry = (struct queue_entry *)urb->context;
	struct queue_entry_priv_usb_bcn *bcn_priv = entry->priv_data;

	if (!test_bit(DEVICE_STATE_ENABLED_RADIO, &entry->queue->rt2x00dev->flags))
		return;

	/*
	 * Check if this was the guardian beacon,
	 * if that was the case we need to send the real beacon now.
	 * Otherwise we should free the sk_buffer, the device
	 * should be doing the rest of the work now.
	 */
	if (bcn_priv->guardian_urb == urb) {
		usb_submit_urb(bcn_priv->urb, GFP_ATOMIC);
	} else if (bcn_priv->urb == urb) {
		dev_kfree_skb(entry->skb);
		entry->skb = NULL;
	}
}
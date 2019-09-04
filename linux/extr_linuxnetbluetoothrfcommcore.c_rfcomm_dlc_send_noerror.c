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
struct sk_buff {int len; } ;
struct rfcomm_dlc {scalar_t__ state; int /*<<< orphan*/  flags; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  addr; int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,struct rfcomm_dlc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RFCOMM_TX_THROTTLED ; 
 int /*<<< orphan*/  rfcomm_make_uih (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_schedule () ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rfcomm_dlc_send_noerror(struct rfcomm_dlc *d, struct sk_buff *skb)
{
	int len = skb->len;

	BT_DBG("dlc %p mtu %d len %d", d, d->mtu, len);

	rfcomm_make_uih(skb, d->addr);
	skb_queue_tail(&d->tx_queue, skb);

	if (d->state == BT_CONNECTED &&
	    !test_bit(RFCOMM_TX_THROTTLED, &d->flags))
		rfcomm_schedule();
}
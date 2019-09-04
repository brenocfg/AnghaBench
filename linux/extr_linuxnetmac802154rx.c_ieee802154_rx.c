#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int flags; } ;
struct ieee802154_local {TYPE_1__ hw; scalar_t__ suspended; } ;

/* Variables and functions */
 int IEEE802154_HW_RX_DROP_BAD_CKSUM ; 
 int IEEE802154_HW_RX_OMIT_CKSUM ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  __ieee802154_rx_handle_packet (struct ieee802154_local*,struct sk_buff*) ; 
 scalar_t__ crc_ccitt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ieee802154_monitors_rx (struct ieee802154_local*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  put_unaligned_le16 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,scalar_t__) ; 
 scalar_t__ softirq_count () ; 

void ieee802154_rx(struct ieee802154_local *local, struct sk_buff *skb)
{
	u16 crc;

	WARN_ON_ONCE(softirq_count() == 0);

	if (local->suspended)
		goto drop;

	/* TODO: When a transceiver omits the checksum here, we
	 * add an own calculated one. This is currently an ugly
	 * solution because the monitor needs a crc here.
	 */
	if (local->hw.flags & IEEE802154_HW_RX_OMIT_CKSUM) {
		crc = crc_ccitt(0, skb->data, skb->len);
		put_unaligned_le16(crc, skb_put(skb, 2));
	}

	rcu_read_lock();

	ieee802154_monitors_rx(local, skb);

	/* Check if transceiver doesn't validate the checksum.
	 * If not we validate the checksum here.
	 */
	if (local->hw.flags & IEEE802154_HW_RX_DROP_BAD_CKSUM) {
		crc = crc_ccitt(0, skb->data, skb->len);
		if (crc) {
			rcu_read_unlock();
			goto drop;
		}
	}
	/* remove crc */
	skb_trim(skb, skb->len - 2);

	__ieee802154_rx_handle_packet(local, skb);

	rcu_read_unlock();

	return;
drop:
	kfree_skb(skb);
}
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
union txhdr_union {int /*<<< orphan*/  txhdr_fw3; } ;
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {size_t len; scalar_t__ data; } ;
struct b43legacy_pioqueue {scalar_t__ need_workarounds; int /*<<< orphan*/  dev; } ;
struct b43legacy_pio_txpacket {int dummy; } ;
struct TYPE_2__ {scalar_t__ nr_frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  IEEE80211_SKB_CB (struct sk_buff*) ; 
 int b43legacy_generate_txhdr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generate_cookie (struct b43legacy_pioqueue*,struct b43legacy_pio_txpacket*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  tx_complete (struct b43legacy_pioqueue*,struct sk_buff*) ; 
 int /*<<< orphan*/  tx_data (struct b43legacy_pioqueue*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  tx_start (struct b43legacy_pioqueue*) ; 

__attribute__((used)) static int pio_tx_write_fragment(struct b43legacy_pioqueue *queue,
				  struct sk_buff *skb,
				  struct b43legacy_pio_txpacket *packet,
				  size_t txhdr_size)
{
	union txhdr_union txhdr_data;
	u8 *txhdr = NULL;
	unsigned int octets;
	int err;

	txhdr = (u8 *)(&txhdr_data.txhdr_fw3);

	B43legacy_WARN_ON(skb_shinfo(skb)->nr_frags != 0);
	err = b43legacy_generate_txhdr(queue->dev,
				 txhdr, skb->data, skb->len,
				 IEEE80211_SKB_CB(skb),
				 generate_cookie(queue, packet));
	if (err)
		return err;

	tx_start(queue);
	octets = skb->len + txhdr_size;
	if (queue->need_workarounds)
		octets--;
	tx_data(queue, txhdr, (u8 *)skb->data, octets);
	tx_complete(queue, skb);

	return 0;
}
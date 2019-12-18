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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nfc_dev {unsigned int tx_headroom; unsigned int tx_tailroom; } ;

/* Variables and functions */
 unsigned int MSG_DONTWAIT ; 
 unsigned int NFC_HEADER_SIZE ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,unsigned int) ; 
 struct sk_buff* sock_alloc_send_skb (struct sock*,unsigned int,unsigned int,unsigned int*) ; 

struct sk_buff *nfc_alloc_send_skb(struct nfc_dev *dev, struct sock *sk,
				   unsigned int flags, unsigned int size,
				   unsigned int *err)
{
	struct sk_buff *skb;
	unsigned int total_size;

	total_size = size +
		dev->tx_headroom + dev->tx_tailroom + NFC_HEADER_SIZE;

	skb = sock_alloc_send_skb(sk, total_size, flags & MSG_DONTWAIT, err);
	if (skb)
		skb_reserve(skb, dev->tx_headroom + NFC_HEADER_SIZE);

	return skb;
}
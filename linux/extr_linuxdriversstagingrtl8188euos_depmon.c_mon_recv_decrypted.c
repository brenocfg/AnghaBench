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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put_data (struct sk_buff*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  unprotect_frame (struct sk_buff*,int,int) ; 

__attribute__((used)) static void mon_recv_decrypted(struct net_device *dev, const u8 *data,
			       int data_len, int iv_len, int icv_len)
{
	struct sk_buff *skb;

	skb = netdev_alloc_skb(dev, data_len);
	if (!skb)
		return;
	skb_put_data(skb, data, data_len);

	/*
	 * Frame data is not encrypted. Strip off protection so
	 * userspace doesn't think that it is.
	 */
	unprotect_frame(skb, iv_len, icv_len);

	skb->ip_summed = CHECKSUM_UNNECESSARY;
	skb->protocol = eth_type_trans(skb, dev);
	netif_rx(skb);
}
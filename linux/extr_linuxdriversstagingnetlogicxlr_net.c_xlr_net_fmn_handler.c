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
typedef  size_t u32 ;
struct xlr_net_priv {int dummy; } ;
struct xlr_adapter {struct net_device** netdev; } ;
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  protocol; } ;
struct nlm_fmn_msg {int msg0; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_OFFSET ; 
 size_t MAC_CRC_LEN ; 
 unsigned char* MAC_SKB_BACK_PTR_SIZE ; 
 unsigned char* bus_to_virt (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 struct xlr_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  send_to_rfr_fifo (struct xlr_net_priv*,void*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 void* xlr_alloc_skb () ; 

__attribute__((used)) static void xlr_net_fmn_handler(int bkt, int src_stnid, int size, int code,
				struct nlm_fmn_msg *msg, void *arg)
{
	struct sk_buff *skb;
	void *skb_data = NULL;
	struct net_device *ndev;
	struct xlr_net_priv *priv;
	u32 port, length;
	unsigned char *addr;
	struct xlr_adapter *adapter = arg;

	length = (msg->msg0 >> 40) & 0x3fff;
	if (length == 0) {
		addr = bus_to_virt(msg->msg0 & 0xffffffffffULL);
		addr = addr - MAC_SKB_BACK_PTR_SIZE;
		skb = (struct sk_buff *)(*(unsigned long *)addr);
		dev_kfree_skb_any((struct sk_buff *)addr);
	} else {
		addr = (unsigned char *)
			bus_to_virt(msg->msg0 & 0xffffffffe0ULL);
		length = length - BYTE_OFFSET - MAC_CRC_LEN;
		port = ((int)msg->msg0) & 0x0f;
		addr = addr - MAC_SKB_BACK_PTR_SIZE;
		skb = (struct sk_buff *)(*(unsigned long *)addr);
		skb->dev = adapter->netdev[port];
		if (!skb->dev)
			return;
		ndev = skb->dev;
		priv = netdev_priv(ndev);

		/* 16 byte IP header align */
		skb_reserve(skb, BYTE_OFFSET);
		skb_put(skb, length);
		skb->protocol = eth_type_trans(skb, skb->dev);
		netif_rx(skb);
		/* Fill rx ring */
		skb_data = xlr_alloc_skb();
		if (skb_data)
			send_to_rfr_fifo(priv, skb_data);
	}
}
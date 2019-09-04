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
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned char X25_IFACE_CONNECT ; 
 struct sk_buff* dev_alloc_skb (int) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  x25_type_trans (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static void lapbeth_connected(struct net_device *dev, int reason)
{
	unsigned char *ptr;
	struct sk_buff *skb = dev_alloc_skb(1);

	if (!skb) {
		pr_err("out of memory\n");
		return;
	}

	ptr  = skb_put(skb, 1);
	*ptr = X25_IFACE_CONNECT;

	skb->protocol = x25_type_trans(skb, dev);
	netif_rx(skb);
}
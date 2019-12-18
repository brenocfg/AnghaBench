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
typedef  int u32 ;
struct sk_buff {scalar_t__ mac_header; scalar_t__ network_header; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BPF_F_INGRESS ; 
 int ERANGE ; 
 int __bpf_rx_skb (struct net_device*,struct sk_buff*) ; 
 int __bpf_tx_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  bpf_push_mac_rcsum (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int __bpf_redirect_common(struct sk_buff *skb, struct net_device *dev,
				 u32 flags)
{
	/* Verify that a link layer header is carried */
	if (unlikely(skb->mac_header >= skb->network_header)) {
		kfree_skb(skb);
		return -ERANGE;
	}

	bpf_push_mac_rcsum(skb);
	return flags & BPF_F_INGRESS ?
	       __bpf_rx_skb(dev, skb) : __bpf_tx_skb(dev, skb);
}
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
typedef  scalar_t__ u32 ;
struct tx_desc {int dummy; } ;
struct sk_buff {scalar_t__ ip_summed; scalar_t__ len; } ;
struct net_device {int dummy; } ;
typedef  int netdev_features_t ;
struct TYPE_2__ {scalar_t__ gso_size; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int GTTCPHO_MAX ; 
 int NETIF_F_CSUM_MASK ; 
 int NETIF_F_GSO_MASK ; 
 int TCPHO_MAX ; 
 scalar_t__ agg_buf_sz ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static netdev_features_t
rtl8152_features_check(struct sk_buff *skb, struct net_device *dev,
		       netdev_features_t features)
{
	u32 mss = skb_shinfo(skb)->gso_size;
	int max_offset = mss ? GTTCPHO_MAX : TCPHO_MAX;
	int offset = skb_transport_offset(skb);

	if ((mss || skb->ip_summed == CHECKSUM_PARTIAL) && offset > max_offset)
		features &= ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
	else if ((skb->len + sizeof(struct tx_desc)) > agg_buf_sz)
		features &= ~NETIF_F_GSO_MASK;

	return features;
}
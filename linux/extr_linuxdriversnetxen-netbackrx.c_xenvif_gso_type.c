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
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int gso_type; } ;

/* Variables and functions */
 int SKB_GSO_TCPV4 ; 
 unsigned int XEN_NETIF_GSO_TYPE_NONE ; 
 unsigned int XEN_NETIF_GSO_TYPE_TCPV4 ; 
 unsigned int XEN_NETIF_GSO_TYPE_TCPV6 ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static unsigned int xenvif_gso_type(struct sk_buff *skb)
{
	if (skb_is_gso(skb)) {
		if (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4)
			return XEN_NETIF_GSO_TYPE_TCPV4;
		else
			return XEN_NETIF_GSO_TYPE_TCPV6;
	}
	return XEN_NETIF_GSO_TYPE_NONE;
}
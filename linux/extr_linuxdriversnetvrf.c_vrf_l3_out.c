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
typedef  int u16 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 struct sk_buff* vrf_ip6_out (struct net_device*,struct sock*,struct sk_buff*) ; 
 struct sk_buff* vrf_ip_out (struct net_device*,struct sock*,struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *vrf_l3_out(struct net_device *vrf_dev,
				  struct sock *sk,
				  struct sk_buff *skb,
				  u16 proto)
{
	switch (proto) {
	case AF_INET:
		return vrf_ip_out(vrf_dev, sk, skb);
	case AF_INET6:
		return vrf_ip6_out(vrf_dev, sk, skb);
	}

	return skb;
}
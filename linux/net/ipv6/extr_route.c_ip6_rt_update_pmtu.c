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
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ip6_rt_update_pmtu (struct dst_entry*,struct sock*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ipv6_hdr (struct sk_buff*) ; 

__attribute__((used)) static void ip6_rt_update_pmtu(struct dst_entry *dst, struct sock *sk,
			       struct sk_buff *skb, u32 mtu)
{
	__ip6_rt_update_pmtu(dst, sk, skb ? ipv6_hdr(skb) : NULL, mtu);
}
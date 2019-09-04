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
struct rtable {int dummy; } ;
struct flowi4 {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ip_rt_update_pmtu (struct rtable*,struct flowi4*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_build_flow_key (struct flowi4*,struct sock*,struct sk_buff*) ; 

__attribute__((used)) static void ip_rt_update_pmtu(struct dst_entry *dst, struct sock *sk,
			      struct sk_buff *skb, u32 mtu)
{
	struct rtable *rt = (struct rtable *) dst;
	struct flowi4 fl4;

	ip_rt_build_flow_key(&fl4, sk, skb);
	__ip_rt_update_pmtu(rt, &fl4, mtu);
}
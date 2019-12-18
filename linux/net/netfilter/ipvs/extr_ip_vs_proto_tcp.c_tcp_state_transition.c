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
struct tcphdr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct ip_vs_proto_data {int dummy; } ;
struct ip_vs_conn {scalar_t__ af; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  _tcph ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int ip_hdrlen (struct sk_buff const*) ; 
 int /*<<< orphan*/  set_tcp_state (struct ip_vs_proto_data*,struct ip_vs_conn*,int,struct tcphdr*) ; 
 struct tcphdr* skb_header_pointer (struct sk_buff const*,int,int,struct tcphdr*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tcp_state_transition(struct ip_vs_conn *cp, int direction,
		     const struct sk_buff *skb,
		     struct ip_vs_proto_data *pd)
{
	struct tcphdr _tcph, *th;

#ifdef CONFIG_IP_VS_IPV6
	int ihl = cp->af == AF_INET ? ip_hdrlen(skb) : sizeof(struct ipv6hdr);
#else
	int ihl = ip_hdrlen(skb);
#endif

	th = skb_header_pointer(skb, ihl, sizeof(_tcph), &_tcph);
	if (th == NULL)
		return;

	spin_lock_bh(&cp->lock);
	set_tcp_state(pd, cp, direction, th);
	spin_unlock_bh(&cp->lock);
}
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
struct sk_buff {int /*<<< orphan*/  dev; scalar_t__ data; } ;
struct net_protocol {int /*<<< orphan*/  (* err_handler ) (struct sk_buff*,int /*<<< orphan*/ ) ;} ;
struct iphdr {int protocol; int ihl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICMP_MIB_INERRORS ; 
 int /*<<< orphan*/  __ICMP_INC_STATS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * inet_protos ; 
 int /*<<< orphan*/  pskb_may_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  raw_icmp_error (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 struct net_protocol* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void icmp_socket_deliver(struct sk_buff *skb, u32 info)
{
	const struct iphdr *iph = (const struct iphdr *) skb->data;
	const struct net_protocol *ipprot;
	int protocol = iph->protocol;

	/* Checkin full IP header plus 8 bytes of protocol to
	 * avoid additional coding at protocol handlers.
	 */
	if (!pskb_may_pull(skb, iph->ihl * 4 + 8)) {
		__ICMP_INC_STATS(dev_net(skb->dev), ICMP_MIB_INERRORS);
		return;
	}

	raw_icmp_error(skb, protocol, info);

	ipprot = rcu_dereference(inet_protos[protocol]);
	if (ipprot && ipprot->err_handler)
		ipprot->err_handler(skb, info);
}
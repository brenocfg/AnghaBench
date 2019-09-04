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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  ignore_df; } ;
struct net {int dummy; } ;
struct iphdr {int frag_off; } ;
struct TYPE_2__ {unsigned int frag_max_size; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_FRAG_NEEDED ; 
 TYPE_1__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPSTATS_MIB_FRAGFAILS ; 
 int /*<<< orphan*/  IP_DF ; 
 int /*<<< orphan*/  IP_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (unsigned int) ; 
 int htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ip_do_fragment (struct net*,struct sock*,struct sk_buff*,int (*) (struct net*,struct sock*,struct sk_buff*)) ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ip_fragment(struct net *net, struct sock *sk, struct sk_buff *skb,
		       unsigned int mtu,
		       int (*output)(struct net *, struct sock *, struct sk_buff *))
{
	struct iphdr *iph = ip_hdr(skb);

	if ((iph->frag_off & htons(IP_DF)) == 0)
		return ip_do_fragment(net, sk, skb, output);

	if (unlikely(!skb->ignore_df ||
		     (IPCB(skb)->frag_max_size &&
		      IPCB(skb)->frag_max_size > mtu))) {
		IP_INC_STATS(net, IPSTATS_MIB_FRAGFAILS);
		icmp_send(skb, ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED,
			  htonl(mtu));
		kfree_skb(skb);
		return -EMSGSIZE;
	}

	return ip_do_fragment(net, sk, skb, output);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sock {int dummy; } ;
struct sk_buff {scalar_t__ data; TYPE_2__* dev; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int ifindex; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ht; } ;

/* Variables and functions */
 int RAW_HTABLE_SIZE ; 
 struct sock* __raw_v4_lookup (struct net*,struct sock*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct net* dev_net (TYPE_2__*) ; 
 int inet_sdif (struct sk_buff*) ; 
 int /*<<< orphan*/  raw_err (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 TYPE_1__ raw_v4_hashinfo ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct sock* sk_head (int /*<<< orphan*/ *) ; 
 struct sock* sk_next (struct sock*) ; 

void raw_icmp_error(struct sk_buff *skb, int protocol, u32 info)
{
	int hash;
	struct sock *raw_sk;
	const struct iphdr *iph;
	struct net *net;

	hash = protocol & (RAW_HTABLE_SIZE - 1);

	read_lock(&raw_v4_hashinfo.lock);
	raw_sk = sk_head(&raw_v4_hashinfo.ht[hash]);
	if (raw_sk) {
		int dif = skb->dev->ifindex;
		int sdif = inet_sdif(skb);

		iph = (const struct iphdr *)skb->data;
		net = dev_net(skb->dev);

		while ((raw_sk = __raw_v4_lookup(net, raw_sk, protocol,
						iph->daddr, iph->saddr,
						dif, sdif)) != NULL) {
			raw_err(raw_sk, skb, info);
			raw_sk = sk_next(raw_sk);
			iph = (const struct iphdr *)skb->data;
		}
	}
	read_unlock(&raw_v4_hashinfo.lock);
}
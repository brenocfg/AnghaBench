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
struct sock {int /*<<< orphan*/  sk_refcnt; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct inet_hashinfo {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 struct sock* __inet6_lookup (struct net*,struct inet_hashinfo*,struct sk_buff*,int,struct in6_addr const*,int /*<<< orphan*/  const,struct in6_addr const*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  refcount_inc_not_zero (int /*<<< orphan*/ *) ; 

struct sock *inet6_lookup(struct net *net, struct inet_hashinfo *hashinfo,
			  struct sk_buff *skb, int doff,
			  const struct in6_addr *saddr, const __be16 sport,
			  const struct in6_addr *daddr, const __be16 dport,
			  const int dif)
{
	struct sock *sk;
	bool refcounted;

	sk = __inet6_lookup(net, hashinfo, skb, doff, saddr, sport, daddr,
			    ntohs(dport), dif, 0, &refcounted);
	if (sk && !refcounted && !refcount_inc_not_zero(&sk->sk_refcnt))
		sk = NULL;
	return sk;
}
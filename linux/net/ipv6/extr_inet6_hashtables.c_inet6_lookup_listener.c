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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net {int dummy; } ;
struct inet_listen_hashbucket {int dummy; } ;
struct inet_hashinfo {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sock*) ; 
 struct in6_addr const in6addr_any ; 
 struct sock* inet6_lhash2_lookup (struct net*,struct inet_listen_hashbucket*,struct sk_buff*,int,struct in6_addr const*,int /*<<< orphan*/  const,struct in6_addr const*,unsigned short const,int const,int const) ; 
 struct inet_listen_hashbucket* inet_lhash2_bucket (struct inet_hashinfo*,unsigned int) ; 
 unsigned int ipv6_portaddr_hash (struct net*,struct in6_addr const*,unsigned short const) ; 

struct sock *inet6_lookup_listener(struct net *net,
		struct inet_hashinfo *hashinfo,
		struct sk_buff *skb, int doff,
		const struct in6_addr *saddr,
		const __be16 sport, const struct in6_addr *daddr,
		const unsigned short hnum, const int dif, const int sdif)
{
	struct inet_listen_hashbucket *ilb2;
	struct sock *result = NULL;
	unsigned int hash2;

	hash2 = ipv6_portaddr_hash(net, daddr, hnum);
	ilb2 = inet_lhash2_bucket(hashinfo, hash2);

	result = inet6_lhash2_lookup(net, ilb2, skb, doff,
				     saddr, sport, daddr, hnum,
				     dif, sdif);
	if (result)
		goto done;

	/* Lookup lhash2 with in6addr_any */
	hash2 = ipv6_portaddr_hash(net, &in6addr_any, hnum);
	ilb2 = inet_lhash2_bucket(hashinfo, hash2);

	result = inet6_lhash2_lookup(net, ilb2, skb, doff,
				     saddr, sport, &in6addr_any, hnum,
				     dif, sdif);
done:
	if (IS_ERR(result))
		return NULL;
	return result;
}
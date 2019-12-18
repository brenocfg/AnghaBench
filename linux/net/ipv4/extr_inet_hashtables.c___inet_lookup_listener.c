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
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  INADDR_ANY ; 
 scalar_t__ IS_ERR (struct sock*) ; 
 int /*<<< orphan*/  const htonl (int /*<<< orphan*/ ) ; 
 struct inet_listen_hashbucket* inet_lhash2_bucket (struct inet_hashinfo*,unsigned int) ; 
 struct sock* inet_lhash2_lookup (struct net*,struct inet_listen_hashbucket*,struct sk_buff*,int,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/  const,unsigned short const,int const,int const) ; 
 unsigned int ipv4_portaddr_hash (struct net*,int /*<<< orphan*/  const,unsigned short const) ; 

struct sock *__inet_lookup_listener(struct net *net,
				    struct inet_hashinfo *hashinfo,
				    struct sk_buff *skb, int doff,
				    const __be32 saddr, __be16 sport,
				    const __be32 daddr, const unsigned short hnum,
				    const int dif, const int sdif)
{
	struct inet_listen_hashbucket *ilb2;
	struct sock *result = NULL;
	unsigned int hash2;

	hash2 = ipv4_portaddr_hash(net, daddr, hnum);
	ilb2 = inet_lhash2_bucket(hashinfo, hash2);

	result = inet_lhash2_lookup(net, ilb2, skb, doff,
				    saddr, sport, daddr, hnum,
				    dif, sdif);
	if (result)
		goto done;

	/* Lookup lhash2 with INADDR_ANY */
	hash2 = ipv4_portaddr_hash(net, htonl(INADDR_ANY), hnum);
	ilb2 = inet_lhash2_bucket(hashinfo, hash2);

	result = inet_lhash2_lookup(net, ilb2, skb, doff,
				    saddr, sport, htonl(INADDR_ANY), hnum,
				    dif, sdif);
done:
	if (IS_ERR(result))
		return NULL;
	return result;
}
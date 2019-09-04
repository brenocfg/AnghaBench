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
typedef  int u8 ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct net {int dummy; } ;
struct in6_addr {int dummy; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 struct sock* inet6_lookup (struct net*,int /*<<< orphan*/ *,struct sk_buff*,int,struct in6_addr const*,int /*<<< orphan*/  const,struct in6_addr const*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_hashinfo ; 
 struct sock* udp6_lib_lookup (struct net*,struct in6_addr const*,int /*<<< orphan*/  const,struct in6_addr const*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sock *
nf_socket_get_sock_v6(struct net *net, struct sk_buff *skb, int doff,
		      const u8 protocol,
		      const struct in6_addr *saddr, const struct in6_addr *daddr,
		      const __be16 sport, const __be16 dport,
		      const struct net_device *in)
{
	switch (protocol) {
	case IPPROTO_TCP:
		return inet6_lookup(net, &tcp_hashinfo, skb, doff,
				    saddr, sport, daddr, dport,
				    in->ifindex);
	case IPPROTO_UDP:
		return udp6_lib_lookup(net, saddr, sport, daddr, dport,
				       in->ifindex);
	}

	return NULL;
}
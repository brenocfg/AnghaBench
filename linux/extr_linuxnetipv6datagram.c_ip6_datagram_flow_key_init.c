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
struct sock {int /*<<< orphan*/  sk_uid; int /*<<< orphan*/  sk_mark; int /*<<< orphan*/  sk_bound_dev_if; int /*<<< orphan*/  sk_v6_daddr; int /*<<< orphan*/  sk_protocol; } ;
struct TYPE_2__ {int /*<<< orphan*/  ipi6_ifindex; } ;
struct ipv6_pinfo {int /*<<< orphan*/  mcast_oif; TYPE_1__ sticky_pktinfo; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  saddr; } ;
struct inet_sock {int /*<<< orphan*/  inet_sport; int /*<<< orphan*/  inet_dport; } ;
struct flowi6 {int /*<<< orphan*/  flowi6_oif; int /*<<< orphan*/  daddr; int /*<<< orphan*/  flowi6_uid; int /*<<< orphan*/  flowlabel; int /*<<< orphan*/  fl6_sport; int /*<<< orphan*/  fl6_dport; int /*<<< orphan*/  flowi6_mark; int /*<<< orphan*/  saddr; int /*<<< orphan*/  flowi6_proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  flowi6_to_flowi (struct flowi6*) ; 
 struct ipv6_pinfo* inet6_sk (struct sock*) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 scalar_t__ ipv6_addr_is_multicast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct flowi6*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  security_sk_classify_flow (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ip6_datagram_flow_key_init(struct flowi6 *fl6, struct sock *sk)
{
	struct inet_sock *inet = inet_sk(sk);
	struct ipv6_pinfo *np = inet6_sk(sk);

	memset(fl6, 0, sizeof(*fl6));
	fl6->flowi6_proto = sk->sk_protocol;
	fl6->daddr = sk->sk_v6_daddr;
	fl6->saddr = np->saddr;
	fl6->flowi6_oif = sk->sk_bound_dev_if;
	fl6->flowi6_mark = sk->sk_mark;
	fl6->fl6_dport = inet->inet_dport;
	fl6->fl6_sport = inet->inet_sport;
	fl6->flowlabel = np->flow_label;
	fl6->flowi6_uid = sk->sk_uid;

	if (!fl6->flowi6_oif)
		fl6->flowi6_oif = np->sticky_pktinfo.ipi6_ifindex;

	if (!fl6->flowi6_oif && ipv6_addr_is_multicast(&fl6->daddr))
		fl6->flowi6_oif = np->mcast_oif;

	security_sk_classify_flow(sk, flowi6_to_flowi(fl6));
}
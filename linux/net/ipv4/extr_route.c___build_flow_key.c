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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sock {int sk_bound_dev_if; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_mark; } ;
struct net {int dummy; } ;
struct iphdr {int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct inet_sock {scalar_t__ hdrincl; } ;
struct flowi4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_RAW ; 
 int /*<<< orphan*/  RT_CONN_FLAGS (struct sock const*) ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  flowi4_init_output (struct flowi4*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock const*) ; 
 int /*<<< orphan*/  sock_net_uid (struct net const*,struct sock const*) ; 

__attribute__((used)) static void __build_flow_key(const struct net *net, struct flowi4 *fl4,
			     const struct sock *sk,
			     const struct iphdr *iph,
			     int oif, u8 tos,
			     u8 prot, u32 mark, int flow_flags)
{
	if (sk) {
		const struct inet_sock *inet = inet_sk(sk);

		oif = sk->sk_bound_dev_if;
		mark = sk->sk_mark;
		tos = RT_CONN_FLAGS(sk);
		prot = inet->hdrincl ? IPPROTO_RAW : sk->sk_protocol;
	}
	flowi4_init_output(fl4, oif, mark, tos,
			   RT_SCOPE_UNIVERSE, prot,
			   flow_flags,
			   iph->daddr, iph->saddr, 0, 0,
			   sock_net_uid(net, sk));
}
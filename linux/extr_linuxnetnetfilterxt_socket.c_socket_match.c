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
struct xt_socket_mtinfo1 {int flags; } ;
struct xt_action_param {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_mark; } ;
struct sk_buff {struct sock* sk; int /*<<< orphan*/  mark; } ;
struct TYPE_2__ {scalar_t__ inet_rcv_saddr; } ;

/* Variables and functions */
 int XT_SOCKET_NOWILDCARD ; 
 int XT_SOCKET_RESTORESKMARK ; 
 int XT_SOCKET_TRANSPARENT ; 
 TYPE_1__* inet_sk (struct sock*) ; 
 int inet_sk_transparent (struct sock*) ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sock* nf_sk_lookup_slow_v4 (int /*<<< orphan*/ ,struct sk_buff const*,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_fullsock (struct sock*) ; 
 int /*<<< orphan*/  sock_gen_put (struct sock*) ; 
 int /*<<< orphan*/  sock_net (struct sock*) ; 
 int /*<<< orphan*/  xt_in (struct xt_action_param*) ; 
 int /*<<< orphan*/  xt_net (struct xt_action_param*) ; 

__attribute__((used)) static bool
socket_match(const struct sk_buff *skb, struct xt_action_param *par,
	     const struct xt_socket_mtinfo1 *info)
{
	struct sk_buff *pskb = (struct sk_buff *)skb;
	struct sock *sk = skb->sk;

	if (sk && !net_eq(xt_net(par), sock_net(sk)))
		sk = NULL;

	if (!sk)
		sk = nf_sk_lookup_slow_v4(xt_net(par), skb, xt_in(par));

	if (sk) {
		bool wildcard;
		bool transparent = true;

		/* Ignore sockets listening on INADDR_ANY,
		 * unless XT_SOCKET_NOWILDCARD is set
		 */
		wildcard = (!(info->flags & XT_SOCKET_NOWILDCARD) &&
			    sk_fullsock(sk) &&
			    inet_sk(sk)->inet_rcv_saddr == 0);

		/* Ignore non-transparent sockets,
		 * if XT_SOCKET_TRANSPARENT is used
		 */
		if (info->flags & XT_SOCKET_TRANSPARENT)
			transparent = inet_sk_transparent(sk);

		if (info->flags & XT_SOCKET_RESTORESKMARK && !wildcard &&
		    transparent && sk_fullsock(sk))
			pskb->mark = sk->sk_mark;

		if (sk != skb->sk)
			sock_gen_put(sk);

		if (wildcard || !transparent)
			sk = NULL;
	}

	return sk != NULL;
}
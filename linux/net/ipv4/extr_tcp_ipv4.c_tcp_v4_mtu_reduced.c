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
typedef  scalar_t__ u32 ;
struct sock {int sk_state; int /*<<< orphan*/  sk_err_soft; } ;
struct inet_sock {scalar_t__ pmtudisc; } ;
struct dst_entry {int dummy; } ;
struct TYPE_4__ {scalar_t__ icsk_pmtu_cookie; } ;
struct TYPE_3__ {scalar_t__ mtu_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMSGSIZE ; 
 scalar_t__ IP_PMTUDISC_DONT ; 
 int TCPF_CLOSE ; 
 int TCPF_LISTEN ; 
 scalar_t__ dst_mtu (struct dst_entry*) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 struct dst_entry* inet_csk_update_pmtu (struct sock*,scalar_t__) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 scalar_t__ ip_dont_fragment (struct sock*,struct dst_entry*) ; 
 scalar_t__ ip_sk_accept_pmtu (struct sock*) ; 
 int /*<<< orphan*/  tcp_simple_retransmit (struct sock*) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_sync_mss (struct sock*,scalar_t__) ; 

void tcp_v4_mtu_reduced(struct sock *sk)
{
	struct inet_sock *inet = inet_sk(sk);
	struct dst_entry *dst;
	u32 mtu;

	if ((1 << sk->sk_state) & (TCPF_LISTEN | TCPF_CLOSE))
		return;
	mtu = tcp_sk(sk)->mtu_info;
	dst = inet_csk_update_pmtu(sk, mtu);
	if (!dst)
		return;

	/* Something is about to be wrong... Remember soft error
	 * for the case, if this connection will not able to recover.
	 */
	if (mtu < dst_mtu(dst) && ip_dont_fragment(sk, dst))
		sk->sk_err_soft = EMSGSIZE;

	mtu = dst_mtu(dst);

	if (inet->pmtudisc != IP_PMTUDISC_DONT &&
	    ip_sk_accept_pmtu(sk) &&
	    inet_csk(sk)->icsk_pmtu_cookie > mtu) {
		tcp_sync_mss(sk, mtu);

		/* Resend the TCP packet because it's
		 * clear that the old packet has been
		 * dropped. This is the new "fast" path mtu
		 * discovery.
		 */
		tcp_simple_retransmit(sk);
	} /* else let the usual retransmit timer handle it */
}
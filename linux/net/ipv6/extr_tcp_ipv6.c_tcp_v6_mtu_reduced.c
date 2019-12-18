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
struct sock {int sk_state; } ;
struct dst_entry {int dummy; } ;
struct TYPE_4__ {scalar_t__ icsk_pmtu_cookie; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtu_info; } ;

/* Variables and functions */
 int TCPF_CLOSE ; 
 int TCPF_LISTEN ; 
 scalar_t__ dst_mtu (struct dst_entry*) ; 
 struct dst_entry* inet6_csk_update_pmtu (struct sock*,int /*<<< orphan*/ ) ; 
 TYPE_2__* inet_csk (struct sock*) ; 
 int /*<<< orphan*/  tcp_simple_retransmit (struct sock*) ; 
 TYPE_1__* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  tcp_sync_mss (struct sock*,scalar_t__) ; 

__attribute__((used)) static void tcp_v6_mtu_reduced(struct sock *sk)
{
	struct dst_entry *dst;

	if ((1 << sk->sk_state) & (TCPF_LISTEN | TCPF_CLOSE))
		return;

	dst = inet6_csk_update_pmtu(sk, tcp_sk(sk)->mtu_info);
	if (!dst)
		return;

	if (inet_csk(sk)->icsk_pmtu_cookie > dst_mtu(dst)) {
		tcp_sync_mss(sk, dst_mtu(dst));
		tcp_simple_retransmit(sk);
	}
}
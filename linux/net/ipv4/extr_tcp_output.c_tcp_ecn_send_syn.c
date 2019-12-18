#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcp_sock {scalar_t__ ecn_flags; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_6__ {int tcp_flags; } ;
struct TYPE_4__ {int sysctl_tcp_ecn; } ;
struct TYPE_5__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  INET_ECN_xmit (struct sock*) ; 
 int /*<<< orphan*/  RTAX_FEATURE_ECN ; 
 int TCPHDR_CWR ; 
 int TCPHDR_ECE ; 
 scalar_t__ TCP_ECN_OK ; 
 TYPE_3__* TCP_SKB_CB (struct sk_buff*) ; 
 struct dst_entry* __sk_dst_get (struct sock*) ; 
 scalar_t__ dst_feature (struct dst_entry const*,int /*<<< orphan*/ ) ; 
 TYPE_2__* sock_net (struct sock*) ; 
 int tcp_bpf_ca_needs_ecn (struct sock*) ; 
 scalar_t__ tcp_ca_needs_ecn (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 

__attribute__((used)) static void tcp_ecn_send_syn(struct sock *sk, struct sk_buff *skb)
{
	struct tcp_sock *tp = tcp_sk(sk);
	bool bpf_needs_ecn = tcp_bpf_ca_needs_ecn(sk);
	bool use_ecn = sock_net(sk)->ipv4.sysctl_tcp_ecn == 1 ||
		tcp_ca_needs_ecn(sk) || bpf_needs_ecn;

	if (!use_ecn) {
		const struct dst_entry *dst = __sk_dst_get(sk);

		if (dst && dst_feature(dst, RTAX_FEATURE_ECN))
			use_ecn = true;
	}

	tp->ecn_flags = 0;

	if (use_ecn) {
		TCP_SKB_CB(skb)->tcp_flags |= TCPHDR_ECE | TCPHDR_CWR;
		tp->ecn_flags = TCP_ECN_OK;
		if (tcp_ca_needs_ecn(sk) || bpf_needs_ecn)
			INET_ECN_xmit(sk);
	}
}
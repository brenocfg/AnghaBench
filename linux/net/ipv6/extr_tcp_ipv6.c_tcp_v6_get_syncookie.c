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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct tcphdr {int dummy; } ;
struct sock {int dummy; } ;
struct ipv6hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cookie_v6_init_sequence (struct ipv6hdr*,struct tcphdr*,scalar_t__*) ; 
 int /*<<< orphan*/  tcp6_request_sock_ops ; 
 scalar_t__ tcp_get_syncookie_mss (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct sock*,struct tcphdr*) ; 
 int /*<<< orphan*/  tcp_request_sock_ipv6_ops ; 
 int /*<<< orphan*/  tcp_synq_overflow (struct sock*) ; 

u16 tcp_v6_get_syncookie(struct sock *sk, struct ipv6hdr *iph,
			 struct tcphdr *th, u32 *cookie)
{
	u16 mss = 0;
#ifdef CONFIG_SYN_COOKIES
	mss = tcp_get_syncookie_mss(&tcp6_request_sock_ops,
				    &tcp_request_sock_ipv6_ops, sk, th);
	if (mss) {
		*cookie = __cookie_v6_init_sequence(iph, th, &mss);
		tcp_synq_overflow(sk);
	}
#endif
	return mss;
}
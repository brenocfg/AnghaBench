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
typedef  int /*<<< orphan*/  u16 ;
struct user_namespace {int dummy; } ;
struct sock {scalar_t__ sk_state; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct inet_diag_req_v2 {int dummy; } ;

/* Variables and functions */
 scalar_t__ TCP_NEW_SYN_RECV ; 
 scalar_t__ TCP_TIME_WAIT ; 
 int inet_csk_diag_fill (struct sock*,struct sk_buff*,struct inet_diag_req_v2 const*,struct user_namespace*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr const*,int) ; 
 int inet_req_diag_fill (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr const*,int) ; 
 int inet_twsk_diag_fill (struct sock*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr const*) ; 

__attribute__((used)) static int sk_diag_fill(struct sock *sk, struct sk_buff *skb,
			const struct inet_diag_req_v2 *r,
			struct user_namespace *user_ns,
			u32 portid, u32 seq, u16 nlmsg_flags,
			const struct nlmsghdr *unlh, bool net_admin)
{
	if (sk->sk_state == TCP_TIME_WAIT)
		return inet_twsk_diag_fill(sk, skb, portid, seq,
					   nlmsg_flags, unlh);

	if (sk->sk_state == TCP_NEW_SYN_RECV)
		return inet_req_diag_fill(sk, skb, portid, seq,
					  nlmsg_flags, unlh, net_admin);

	return inet_csk_diag_fill(sk, skb, r, user_ns, portid, seq,
				  nlmsg_flags, unlh, net_admin);
}
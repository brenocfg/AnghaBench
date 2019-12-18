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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct inet_diag_req_v2 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  inet_csk (struct sock*) ; 
 int inet_sk_diag_fill (struct sock*,int /*<<< orphan*/ ,struct sk_buff*,struct inet_diag_req_v2 const*,struct user_namespace*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nlmsghdr const*,int) ; 

__attribute__((used)) static int inet_csk_diag_fill(struct sock *sk,
			      struct sk_buff *skb,
			      const struct inet_diag_req_v2 *req,
			      struct user_namespace *user_ns,
			      u32 portid, u32 seq, u16 nlmsg_flags,
			      const struct nlmsghdr *unlh,
			      bool net_admin)
{
	return inet_sk_diag_fill(sk, inet_csk(sk), skb, req, user_ns,
				 portid, seq, nlmsg_flags, unlh, net_admin);
}
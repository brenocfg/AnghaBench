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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {TYPE_1__* nlh; int /*<<< orphan*/  skb; } ;
struct inet_diag_req_v2 {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  portid; int /*<<< orphan*/  sk; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 TYPE_2__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int inet_csk_diag_fill (struct sock*,struct sk_buff*,struct inet_diag_req_v2 const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  inet_diag_bc_sk (struct nlattr const*,struct sock*) ; 
 int /*<<< orphan*/  sk_user_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int inet_csk_diag_dump(struct sock *sk,
			      struct sk_buff *skb,
			      struct netlink_callback *cb,
			      const struct inet_diag_req_v2 *r,
			      const struct nlattr *bc,
			      bool net_admin)
{
	if (!inet_diag_bc_sk(bc, sk))
		return 0;

	return inet_csk_diag_fill(sk, skb, r,
				  sk_user_ns(NETLINK_CB(cb->skb).sk),
				  NETLINK_CB(cb->skb).portid,
				  cb->nlh->nlmsg_seq, NLM_F_MULTI, cb->nlh,
				  net_admin);
}
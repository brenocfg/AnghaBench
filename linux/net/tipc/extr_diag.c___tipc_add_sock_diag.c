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
struct tipc_sock_diag_req {int /*<<< orphan*/  tidiag_states; } ;
struct tipc_sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct netlink_callback {int /*<<< orphan*/  nlh; } ;

/* Variables and functions */
 int EMSGSIZE ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int /*<<< orphan*/  SOCK_DIAG_BY_FAMILY ; 
 int /*<<< orphan*/  __tipc_diag_gen_cookie ; 
 struct tipc_sock_diag_req* nlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put_answer (struct sk_buff*,struct netlink_callback*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tipc_sk_fill_sock_diag (struct sk_buff*,struct netlink_callback*,struct tipc_sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __tipc_add_sock_diag(struct sk_buff *skb,
				struct netlink_callback *cb,
				struct tipc_sock *tsk)
{
	struct tipc_sock_diag_req *req = nlmsg_data(cb->nlh);
	struct nlmsghdr *nlh;
	int err;

	nlh = nlmsg_put_answer(skb, cb, SOCK_DIAG_BY_FAMILY, 0,
			       NLM_F_MULTI);
	if (!nlh)
		return -EMSGSIZE;

	err = tipc_sk_fill_sock_diag(skb, cb, tsk, req->tidiag_states,
				     __tipc_diag_gen_cookie);
	if (err)
		return err;

	nlmsg_end(skb, nlh);
	return 0;
}
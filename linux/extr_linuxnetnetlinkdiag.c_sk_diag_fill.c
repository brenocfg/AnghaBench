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
struct sock {int /*<<< orphan*/  sk_state; int /*<<< orphan*/  sk_protocol; int /*<<< orphan*/  sk_type; } ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct netlink_sock {int /*<<< orphan*/  dst_group; int /*<<< orphan*/  dst_portid; int /*<<< orphan*/  portid; } ;
struct netlink_diag_req {int ndiag_show; } ;
struct netlink_diag_msg {int ndiag_ino; int /*<<< orphan*/  ndiag_cookie; int /*<<< orphan*/  ndiag_dst_group; int /*<<< orphan*/  ndiag_dst_portid; int /*<<< orphan*/  ndiag_portid; int /*<<< orphan*/  ndiag_state; int /*<<< orphan*/  ndiag_protocol; int /*<<< orphan*/  ndiag_type; int /*<<< orphan*/  ndiag_family; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NETLINK ; 
 int EMSGSIZE ; 
 int NDIAG_SHOW_FLAGS ; 
 int NDIAG_SHOW_GROUPS ; 
 int NDIAG_SHOW_MEMINFO ; 
 int /*<<< orphan*/  NETLINK_DIAG_MEMINFO ; 
 int /*<<< orphan*/  SOCK_DIAG_BY_FAMILY ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct netlink_diag_msg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_diag_dump_groups (struct sock*,struct sk_buff*) ; 
 scalar_t__ sk_diag_put_flags (struct sock*,struct sk_buff*) ; 
 scalar_t__ sock_diag_put_meminfo (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_diag_save_cookie (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sk_diag_fill(struct sock *sk, struct sk_buff *skb,
			struct netlink_diag_req *req,
			u32 portid, u32 seq, u32 flags, int sk_ino)
{
	struct nlmsghdr *nlh;
	struct netlink_diag_msg *rep;
	struct netlink_sock *nlk = nlk_sk(sk);

	nlh = nlmsg_put(skb, portid, seq, SOCK_DIAG_BY_FAMILY, sizeof(*rep),
			flags);
	if (!nlh)
		return -EMSGSIZE;

	rep = nlmsg_data(nlh);
	rep->ndiag_family	= AF_NETLINK;
	rep->ndiag_type		= sk->sk_type;
	rep->ndiag_protocol	= sk->sk_protocol;
	rep->ndiag_state	= sk->sk_state;

	rep->ndiag_ino		= sk_ino;
	rep->ndiag_portid	= nlk->portid;
	rep->ndiag_dst_portid	= nlk->dst_portid;
	rep->ndiag_dst_group	= nlk->dst_group;
	sock_diag_save_cookie(sk, rep->ndiag_cookie);

	if ((req->ndiag_show & NDIAG_SHOW_GROUPS) &&
	    sk_diag_dump_groups(sk, skb))
		goto out_nlmsg_trim;

	if ((req->ndiag_show & NDIAG_SHOW_MEMINFO) &&
	    sock_diag_put_meminfo(sk, skb, NETLINK_DIAG_MEMINFO))
		goto out_nlmsg_trim;

	if ((req->ndiag_show & NDIAG_SHOW_FLAGS) &&
	    sk_diag_put_flags(sk, skb))
		goto out_nlmsg_trim;

	nlmsg_end(skb, nlh);
	return 0;

out_nlmsg_trim:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}
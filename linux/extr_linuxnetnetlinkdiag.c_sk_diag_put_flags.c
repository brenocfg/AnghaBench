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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct netlink_sock {int flags; scalar_t__ cb_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDIAG_FLAG_BROADCAST_ERROR ; 
 int /*<<< orphan*/  NDIAG_FLAG_CAP_ACK ; 
 int /*<<< orphan*/  NDIAG_FLAG_CB_RUNNING ; 
 int /*<<< orphan*/  NDIAG_FLAG_LISTEN_ALL_NSID ; 
 int /*<<< orphan*/  NDIAG_FLAG_NO_ENOBUFS ; 
 int /*<<< orphan*/  NDIAG_FLAG_PKTINFO ; 
 int /*<<< orphan*/  NETLINK_DIAG_FLAGS ; 
 int NETLINK_F_BROADCAST_SEND_ERROR ; 
 int NETLINK_F_CAP_ACK ; 
 int NETLINK_F_LISTEN_ALL_NSID ; 
 int NETLINK_F_RECV_NO_ENOBUFS ; 
 int NETLINK_F_RECV_PKTINFO ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netlink_sock* nlk_sk (struct sock*) ; 

__attribute__((used)) static int sk_diag_put_flags(struct sock *sk, struct sk_buff *skb)
{
	struct netlink_sock *nlk = nlk_sk(sk);
	u32 flags = 0;

	if (nlk->cb_running)
		flags |= NDIAG_FLAG_CB_RUNNING;
	if (nlk->flags & NETLINK_F_RECV_PKTINFO)
		flags |= NDIAG_FLAG_PKTINFO;
	if (nlk->flags & NETLINK_F_BROADCAST_SEND_ERROR)
		flags |= NDIAG_FLAG_BROADCAST_ERROR;
	if (nlk->flags & NETLINK_F_RECV_NO_ENOBUFS)
		flags |= NDIAG_FLAG_NO_ENOBUFS;
	if (nlk->flags & NETLINK_F_LISTEN_ALL_NSID)
		flags |= NDIAG_FLAG_LISTEN_ALL_NSID;
	if (nlk->flags & NETLINK_F_CAP_ACK)
		flags |= NDIAG_FLAG_CAP_ACK;

	return nla_put_u32(skb, NETLINK_DIAG_FLAGS, flags);
}
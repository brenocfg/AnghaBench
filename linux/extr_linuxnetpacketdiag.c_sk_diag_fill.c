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
struct user_namespace {int dummy; } ;
struct sock {int /*<<< orphan*/  sk_type; } ;
struct sk_buff {int dummy; } ;
struct packet_sock {int /*<<< orphan*/  num; } ;
struct packet_diag_req {int pdiag_show; } ;
struct packet_diag_msg {int pdiag_ino; int /*<<< orphan*/  pdiag_cookie; int /*<<< orphan*/  pdiag_num; int /*<<< orphan*/  pdiag_type; int /*<<< orphan*/  pdiag_family; } ;
struct nlmsghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_PACKET ; 
 int EMSGSIZE ; 
 int /*<<< orphan*/  PACKET_DIAG_FILTER ; 
 int /*<<< orphan*/  PACKET_DIAG_MEMINFO ; 
 int /*<<< orphan*/  PACKET_DIAG_UID ; 
 int PACKET_SHOW_FANOUT ; 
 int PACKET_SHOW_FILTER ; 
 int PACKET_SHOW_INFO ; 
 int PACKET_SHOW_MCLIST ; 
 int PACKET_SHOW_MEMINFO ; 
 int PACKET_SHOW_RING_CFG ; 
 int /*<<< orphan*/  SOCK_DIAG_BY_FAMILY ; 
 int /*<<< orphan*/  from_kuid_munged (struct user_namespace*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_cancel (struct sk_buff*,struct nlmsghdr*) ; 
 struct packet_diag_msg* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  nlmsg_end (struct sk_buff*,struct nlmsghdr*) ; 
 struct nlmsghdr* nlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ pdiag_put_fanout (struct packet_sock*,struct sk_buff*) ; 
 scalar_t__ pdiag_put_info (struct packet_sock*,struct sk_buff*) ; 
 scalar_t__ pdiag_put_mclist (struct packet_sock*,struct sk_buff*) ; 
 scalar_t__ pdiag_put_rings_cfg (struct packet_sock*,struct sk_buff*) ; 
 struct packet_sock* pkt_sk (struct sock*) ; 
 scalar_t__ sock_diag_put_filterinfo (int,struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ sock_diag_put_meminfo (struct sock*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_diag_save_cookie (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_i_uid (struct sock*) ; 

__attribute__((used)) static int sk_diag_fill(struct sock *sk, struct sk_buff *skb,
			struct packet_diag_req *req,
			bool may_report_filterinfo,
			struct user_namespace *user_ns,
			u32 portid, u32 seq, u32 flags, int sk_ino)
{
	struct nlmsghdr *nlh;
	struct packet_diag_msg *rp;
	struct packet_sock *po = pkt_sk(sk);

	nlh = nlmsg_put(skb, portid, seq, SOCK_DIAG_BY_FAMILY, sizeof(*rp), flags);
	if (!nlh)
		return -EMSGSIZE;

	rp = nlmsg_data(nlh);
	rp->pdiag_family = AF_PACKET;
	rp->pdiag_type = sk->sk_type;
	rp->pdiag_num = ntohs(po->num);
	rp->pdiag_ino = sk_ino;
	sock_diag_save_cookie(sk, rp->pdiag_cookie);

	if ((req->pdiag_show & PACKET_SHOW_INFO) &&
			pdiag_put_info(po, skb))
		goto out_nlmsg_trim;

	if ((req->pdiag_show & PACKET_SHOW_INFO) &&
	    nla_put_u32(skb, PACKET_DIAG_UID,
			from_kuid_munged(user_ns, sock_i_uid(sk))))
		goto out_nlmsg_trim;

	if ((req->pdiag_show & PACKET_SHOW_MCLIST) &&
			pdiag_put_mclist(po, skb))
		goto out_nlmsg_trim;

	if ((req->pdiag_show & PACKET_SHOW_RING_CFG) &&
			pdiag_put_rings_cfg(po, skb))
		goto out_nlmsg_trim;

	if ((req->pdiag_show & PACKET_SHOW_FANOUT) &&
			pdiag_put_fanout(po, skb))
		goto out_nlmsg_trim;

	if ((req->pdiag_show & PACKET_SHOW_MEMINFO) &&
	    sock_diag_put_meminfo(sk, skb, PACKET_DIAG_MEMINFO))
		goto out_nlmsg_trim;

	if ((req->pdiag_show & PACKET_SHOW_FILTER) &&
	    sock_diag_put_filterinfo(may_report_filterinfo, sk, skb,
				     PACKET_DIAG_FILTER))
		goto out_nlmsg_trim;

	nlmsg_end(skb, nlh);
	return 0;

out_nlmsg_trim:
	nlmsg_cancel(skb, nlh);
	return -EMSGSIZE;
}
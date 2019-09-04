#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sock {scalar_t__ sk_family; } ;
struct sk_buff {struct sock* sk; } ;
struct TYPE_5__ {struct sock* sk; } ;
struct sctp_endpoint {int /*<<< orphan*/  asocs; TYPE_1__ base; } ;
struct sctp_comm_param {int /*<<< orphan*/  net_admin; struct inet_diag_req_v2* r; struct netlink_callback* cb; struct sk_buff* skb; } ;
struct netlink_callback {scalar_t__* args; TYPE_3__* nlh; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct inet_sock {scalar_t__ inet_sport; scalar_t__ inet_dport; } ;
struct TYPE_6__ {scalar_t__ idiag_sport; scalar_t__ idiag_dport; } ;
struct inet_diag_req_v2 {int idiag_states; scalar_t__ sdiag_family; TYPE_2__ id; } ;
struct TYPE_8__ {int /*<<< orphan*/  portid; int /*<<< orphan*/  sk; } ;
struct TYPE_7__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 TYPE_4__ NETLINK_CB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NLM_F_MULTI ; 
 int TCPF_LISTEN ; 
 scalar_t__ inet_sctp_diag_fill (struct sock*,int /*<<< orphan*/ *,struct sk_buff*,struct inet_diag_req_v2 const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_eq (struct net*,struct net*) ; 
 int /*<<< orphan*/  sk_user_ns (int /*<<< orphan*/ ) ; 
 struct net* sock_net (struct sock*) ; 

__attribute__((used)) static int sctp_ep_dump(struct sctp_endpoint *ep, void *p)
{
	struct sctp_comm_param *commp = p;
	struct sock *sk = ep->base.sk;
	struct sk_buff *skb = commp->skb;
	struct netlink_callback *cb = commp->cb;
	const struct inet_diag_req_v2 *r = commp->r;
	struct net *net = sock_net(skb->sk);
	struct inet_sock *inet = inet_sk(sk);
	int err = 0;

	if (!net_eq(sock_net(sk), net))
		goto out;

	if (cb->args[4] < cb->args[1])
		goto next;

	if (!(r->idiag_states & TCPF_LISTEN) && !list_empty(&ep->asocs))
		goto next;

	if (r->sdiag_family != AF_UNSPEC &&
	    sk->sk_family != r->sdiag_family)
		goto next;

	if (r->id.idiag_sport != inet->inet_sport &&
	    r->id.idiag_sport)
		goto next;

	if (r->id.idiag_dport != inet->inet_dport &&
	    r->id.idiag_dport)
		goto next;

	if (inet_sctp_diag_fill(sk, NULL, skb, r,
				sk_user_ns(NETLINK_CB(cb->skb).sk),
				NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq, NLM_F_MULTI,
				cb->nlh, commp->net_admin) < 0) {
		err = 2;
		goto out;
	}
next:
	cb->args[4]++;
out:
	return err;
}
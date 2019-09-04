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
struct TYPE_8__ {void* sin6_family; int /*<<< orphan*/  sin6_addr; int /*<<< orphan*/  sin6_port; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_6__ {scalar_t__ sin_family; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; } ;
union sctp_addr {TYPE_4__ v6; TYPE_2__ v4; } ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct sctp_comm_param {int /*<<< orphan*/  net_admin; struct nlmsghdr const* nlh; struct inet_diag_req_v2 const* r; struct sk_buff* skb; } ;
struct nlmsghdr {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * idiag_dst; int /*<<< orphan*/  idiag_dport; int /*<<< orphan*/ * idiag_src; int /*<<< orphan*/  idiag_sport; } ;
struct inet_diag_req_v2 {scalar_t__ sdiag_family; TYPE_3__ id; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 void* AF_INET6 ; 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netlink_net_capable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int sctp_transport_lookup_process (int /*<<< orphan*/ ,struct net*,union sctp_addr*,union sctp_addr*,struct sctp_comm_param*) ; 
 int /*<<< orphan*/  sctp_tsp_dump_one ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_diag_dump_one(struct sk_buff *in_skb,
			      const struct nlmsghdr *nlh,
			      const struct inet_diag_req_v2 *req)
{
	struct net *net = sock_net(in_skb->sk);
	union sctp_addr laddr, paddr;
	struct sctp_comm_param commp = {
		.skb = in_skb,
		.r = req,
		.nlh = nlh,
		.net_admin = netlink_net_capable(in_skb, CAP_NET_ADMIN),
	};

	if (req->sdiag_family == AF_INET) {
		laddr.v4.sin_port = req->id.idiag_sport;
		laddr.v4.sin_addr.s_addr = req->id.idiag_src[0];
		laddr.v4.sin_family = AF_INET;

		paddr.v4.sin_port = req->id.idiag_dport;
		paddr.v4.sin_addr.s_addr = req->id.idiag_dst[0];
		paddr.v4.sin_family = AF_INET;
	} else {
		laddr.v6.sin6_port = req->id.idiag_sport;
		memcpy(&laddr.v6.sin6_addr, req->id.idiag_src,
		       sizeof(laddr.v6.sin6_addr));
		laddr.v6.sin6_family = AF_INET6;

		paddr.v6.sin6_port = req->id.idiag_dport;
		memcpy(&paddr.v6.sin6_addr, req->id.idiag_dst,
		       sizeof(paddr.v6.sin6_addr));
		paddr.v6.sin6_family = AF_INET6;
	}

	return sctp_transport_lookup_process(sctp_tsp_dump_one,
					     net, &laddr, &paddr, &commp);
}
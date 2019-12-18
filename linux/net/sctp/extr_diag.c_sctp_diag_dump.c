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
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  sk; } ;
struct sctp_comm_param {int /*<<< orphan*/  net_admin; struct inet_diag_req_v2 const* r; struct netlink_callback* cb; struct sk_buff* skb; } ;
struct nlattr {int dummy; } ;
struct netlink_callback {int* args; int /*<<< orphan*/  skb; } ;
struct net {int dummy; } ;
struct inet_diag_req_v2 {int idiag_states; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int TCPF_CLOSE ; 
 int TCPF_LISTEN ; 
 int /*<<< orphan*/  netlink_net_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ep_dump ; 
 scalar_t__ sctp_for_each_endpoint (int /*<<< orphan*/ ,struct sctp_comm_param*) ; 
 int /*<<< orphan*/  sctp_for_each_transport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net*,int*,struct sctp_comm_param*) ; 
 int /*<<< orphan*/  sctp_sock_dump ; 
 int /*<<< orphan*/  sctp_sock_filter ; 
 struct net* sock_net (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sctp_diag_dump(struct sk_buff *skb, struct netlink_callback *cb,
			   const struct inet_diag_req_v2 *r, struct nlattr *bc)
{
	u32 idiag_states = r->idiag_states;
	struct net *net = sock_net(skb->sk);
	struct sctp_comm_param commp = {
		.skb = skb,
		.cb = cb,
		.r = r,
		.net_admin = netlink_net_capable(cb->skb, CAP_NET_ADMIN),
	};
	int pos = cb->args[2];

	/* eps hashtable dumps
	 * args:
	 * 0 : if it will traversal listen sock
	 * 1 : to record the sock pos of this time's traversal
	 * 4 : to work as a temporary variable to traversal list
	 */
	if (cb->args[0] == 0) {
		if (!(idiag_states & TCPF_LISTEN))
			goto skip;
		if (sctp_for_each_endpoint(sctp_ep_dump, &commp))
			goto done;
skip:
		cb->args[0] = 1;
		cb->args[1] = 0;
		cb->args[4] = 0;
	}

	/* asocs by transport hashtable dump
	 * args:
	 * 1 : to record the assoc pos of this time's traversal
	 * 2 : to record the transport pos of this time's traversal
	 * 3 : to mark if we have dumped the ep info of the current asoc
	 * 4 : to work as a temporary variable to traversal list
	 * 5 : to save the sk we get from travelsing the tsp list.
	 */
	if (!(idiag_states & ~(TCPF_LISTEN | TCPF_CLOSE)))
		goto done;

	sctp_for_each_transport(sctp_sock_filter, sctp_sock_dump,
				net, &pos, &commp);
	cb->args[2] = pos;

done:
	cb->args[1] = cb->args[4];
	cb->args[4] = 0;
}
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
typedef  int /*<<< orphan*/  u_int16_t ;
struct nf_proto_net {int /*<<< orphan*/  users; } ;
struct nf_tcp_net {int /*<<< orphan*/  tcp_max_retrans; int /*<<< orphan*/  tcp_be_liberal; int /*<<< orphan*/  tcp_loose; void** timeouts; struct nf_proto_net pn; } ;
struct net {int dummy; } ;

/* Variables and functions */
 size_t TCP_CONNTRACK_SYN_SENT ; 
 int TCP_CONNTRACK_TIMEOUT_MAX ; 
 int /*<<< orphan*/  nf_ct_tcp_be_liberal ; 
 int /*<<< orphan*/  nf_ct_tcp_loose ; 
 int /*<<< orphan*/  nf_ct_tcp_max_retrans ; 
 int tcp_kmemdup_sysctl_table (struct nf_proto_net*,struct nf_tcp_net*) ; 
 struct nf_tcp_net* tcp_pernet (struct net*) ; 
 void** tcp_timeouts ; 

__attribute__((used)) static int tcp_init_net(struct net *net, u_int16_t proto)
{
	struct nf_tcp_net *tn = tcp_pernet(net);
	struct nf_proto_net *pn = &tn->pn;

	if (!pn->users) {
		int i;

		for (i = 0; i < TCP_CONNTRACK_TIMEOUT_MAX; i++)
			tn->timeouts[i] = tcp_timeouts[i];

		/* timeouts[0] is unused, make it same as SYN_SENT so
		 * ->timeouts[0] contains 'new' timeout, like udp or icmp.
		 */
		tn->timeouts[0] = tcp_timeouts[TCP_CONNTRACK_SYN_SENT];
		tn->tcp_loose = nf_ct_tcp_loose;
		tn->tcp_be_liberal = nf_ct_tcp_be_liberal;
		tn->tcp_max_retrans = nf_ct_tcp_max_retrans;
	}

	return tcp_kmemdup_sysctl_table(pn, tn);
}
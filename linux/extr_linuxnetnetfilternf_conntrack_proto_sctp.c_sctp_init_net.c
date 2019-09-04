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
struct nf_sctp_net {void** timeouts; struct nf_proto_net pn; } ;
struct net {int dummy; } ;

/* Variables and functions */
 size_t SCTP_CONNTRACK_CLOSED ; 
 int SCTP_CONNTRACK_MAX ; 
 int sctp_kmemdup_sysctl_table (struct nf_proto_net*,struct nf_sctp_net*) ; 
 struct nf_sctp_net* sctp_pernet (struct net*) ; 
 void** sctp_timeouts ; 

__attribute__((used)) static int sctp_init_net(struct net *net, u_int16_t proto)
{
	struct nf_sctp_net *sn = sctp_pernet(net);
	struct nf_proto_net *pn = &sn->pn;

	if (!pn->users) {
		int i;

		for (i = 0; i < SCTP_CONNTRACK_MAX; i++)
			sn->timeouts[i] = sctp_timeouts[i];

		/* timeouts[0] is unused, init it so ->timeouts[0] contains
		 * 'new' timeout, like udp or icmp.
		 */
		sn->timeouts[0] = sctp_timeouts[SCTP_CONNTRACK_CLOSED];
	}

	return sctp_kmemdup_sysctl_table(pn, sn);
}
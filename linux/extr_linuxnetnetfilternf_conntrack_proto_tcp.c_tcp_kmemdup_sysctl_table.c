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
struct nf_tcp_net {int dummy; } ;
struct nf_proto_net {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int tcp_kmemdup_sysctl_table(struct nf_proto_net *pn,
				    struct nf_tcp_net *tn)
{
#ifdef CONFIG_SYSCTL
	if (pn->ctl_table)
		return 0;

	pn->ctl_table = kmemdup(tcp_sysctl_table,
				sizeof(tcp_sysctl_table),
				GFP_KERNEL);
	if (!pn->ctl_table)
		return -ENOMEM;

	pn->ctl_table[0].data = &tn->timeouts[TCP_CONNTRACK_SYN_SENT];
	pn->ctl_table[1].data = &tn->timeouts[TCP_CONNTRACK_SYN_RECV];
	pn->ctl_table[2].data = &tn->timeouts[TCP_CONNTRACK_ESTABLISHED];
	pn->ctl_table[3].data = &tn->timeouts[TCP_CONNTRACK_FIN_WAIT];
	pn->ctl_table[4].data = &tn->timeouts[TCP_CONNTRACK_CLOSE_WAIT];
	pn->ctl_table[5].data = &tn->timeouts[TCP_CONNTRACK_LAST_ACK];
	pn->ctl_table[6].data = &tn->timeouts[TCP_CONNTRACK_TIME_WAIT];
	pn->ctl_table[7].data = &tn->timeouts[TCP_CONNTRACK_CLOSE];
	pn->ctl_table[8].data = &tn->timeouts[TCP_CONNTRACK_RETRANS];
	pn->ctl_table[9].data = &tn->timeouts[TCP_CONNTRACK_UNACK];
	pn->ctl_table[10].data = &tn->tcp_loose;
	pn->ctl_table[11].data = &tn->tcp_be_liberal;
	pn->ctl_table[12].data = &tn->tcp_max_retrans;
#endif
	return 0;
}
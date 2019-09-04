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
struct nf_sctp_net {int dummy; } ;
struct nf_proto_net {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int sctp_kmemdup_sysctl_table(struct nf_proto_net *pn,
				     struct nf_sctp_net *sn)
{
#ifdef CONFIG_SYSCTL
	if (pn->ctl_table)
		return 0;

	pn->ctl_table = kmemdup(sctp_sysctl_table,
				sizeof(sctp_sysctl_table),
				GFP_KERNEL);
	if (!pn->ctl_table)
		return -ENOMEM;

	pn->ctl_table[0].data = &sn->timeouts[SCTP_CONNTRACK_CLOSED];
	pn->ctl_table[1].data = &sn->timeouts[SCTP_CONNTRACK_COOKIE_WAIT];
	pn->ctl_table[2].data = &sn->timeouts[SCTP_CONNTRACK_COOKIE_ECHOED];
	pn->ctl_table[3].data = &sn->timeouts[SCTP_CONNTRACK_ESTABLISHED];
	pn->ctl_table[4].data = &sn->timeouts[SCTP_CONNTRACK_SHUTDOWN_SENT];
	pn->ctl_table[5].data = &sn->timeouts[SCTP_CONNTRACK_SHUTDOWN_RECD];
	pn->ctl_table[6].data = &sn->timeouts[SCTP_CONNTRACK_SHUTDOWN_ACK_SENT];
	pn->ctl_table[7].data = &sn->timeouts[SCTP_CONNTRACK_HEARTBEAT_SENT];
	pn->ctl_table[8].data = &sn->timeouts[SCTP_CONNTRACK_HEARTBEAT_ACKED];
#endif
	return 0;
}
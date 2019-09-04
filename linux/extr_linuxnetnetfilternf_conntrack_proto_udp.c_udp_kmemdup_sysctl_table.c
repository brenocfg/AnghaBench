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
struct nf_udp_net {int dummy; } ;
struct nf_proto_net {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int udp_kmemdup_sysctl_table(struct nf_proto_net *pn,
				    struct nf_udp_net *un)
{
#ifdef CONFIG_SYSCTL
	if (pn->ctl_table)
		return 0;
	pn->ctl_table = kmemdup(udp_sysctl_table,
				sizeof(udp_sysctl_table),
				GFP_KERNEL);
	if (!pn->ctl_table)
		return -ENOMEM;
	pn->ctl_table[0].data = &un->timeouts[UDP_CT_UNREPLIED];
	pn->ctl_table[1].data = &un->timeouts[UDP_CT_REPLIED];
#endif
	return 0;
}
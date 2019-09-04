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
struct nf_proto_net {int dummy; } ;
struct nf_dccp_net {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int dccp_kmemdup_sysctl_table(struct net *net, struct nf_proto_net *pn,
				     struct nf_dccp_net *dn)
{
#ifdef CONFIG_SYSCTL
	if (pn->ctl_table)
		return 0;

	pn->ctl_table = kmemdup(dccp_sysctl_table,
				sizeof(dccp_sysctl_table),
				GFP_KERNEL);
	if (!pn->ctl_table)
		return -ENOMEM;

	pn->ctl_table[0].data = &dn->dccp_timeout[CT_DCCP_REQUEST];
	pn->ctl_table[1].data = &dn->dccp_timeout[CT_DCCP_RESPOND];
	pn->ctl_table[2].data = &dn->dccp_timeout[CT_DCCP_PARTOPEN];
	pn->ctl_table[3].data = &dn->dccp_timeout[CT_DCCP_OPEN];
	pn->ctl_table[4].data = &dn->dccp_timeout[CT_DCCP_CLOSEREQ];
	pn->ctl_table[5].data = &dn->dccp_timeout[CT_DCCP_CLOSING];
	pn->ctl_table[6].data = &dn->dccp_timeout[CT_DCCP_TIMEWAIT];
	pn->ctl_table[7].data = &dn->dccp_loose;

	/* Don't export sysctls to unprivileged users */
	if (net->user_ns != &init_user_ns)
		pn->ctl_table[0].procname = NULL;
#endif
	return 0;
}
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
struct nf_conntrack_l4proto {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static
void nf_ct_l4proto_unregister_sysctl(struct net *net,
				struct nf_proto_net *pn,
				const struct nf_conntrack_l4proto *l4proto)
{
#ifdef CONFIG_SYSCTL
	if (pn->ctl_table_header != NULL)
		nf_ct_unregister_sysctl(&pn->ctl_table_header,
					&pn->ctl_table,
					pn->users);
#endif /* CONFIG_SYSCTL */
}
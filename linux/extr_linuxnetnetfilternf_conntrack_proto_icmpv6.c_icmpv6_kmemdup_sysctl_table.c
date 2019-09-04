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
struct nf_icmp_net {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int icmpv6_kmemdup_sysctl_table(struct nf_proto_net *pn,
				       struct nf_icmp_net *in)
{
#ifdef CONFIG_SYSCTL
	pn->ctl_table = kmemdup(icmpv6_sysctl_table,
				sizeof(icmpv6_sysctl_table),
				GFP_KERNEL);
	if (!pn->ctl_table)
		return -ENOMEM;

	pn->ctl_table[0].data = &in->timeout;
#endif
	return 0;
}
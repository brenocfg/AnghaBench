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
int nf_ct_l4proto_register_sysctl(struct net *net,
				  struct nf_proto_net *pn,
				  const struct nf_conntrack_l4proto *l4proto)
{
	int err = 0;

#ifdef CONFIG_SYSCTL
	if (pn->ctl_table != NULL) {
		err = nf_ct_register_sysctl(net,
					    &pn->ctl_table_header,
					    "net/netfilter",
					    pn->ctl_table);
		if (err < 0) {
			if (!pn->users) {
				kfree(pn->ctl_table);
				pn->ctl_table = NULL;
			}
		}
	}
#endif /* CONFIG_SYSCTL */
	return err;
}
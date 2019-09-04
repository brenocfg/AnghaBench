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
struct nf_conntrack_l4proto {scalar_t__ l3proto; int /*<<< orphan*/  l4proto; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PF_INET6 ; 
 int nf_ct_l4proto_register_one (struct nf_conntrack_l4proto const* const) ; 
 int /*<<< orphan*/  nf_ct_l4proto_unregister (struct nf_conntrack_l4proto const* const*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nf_ct_l4proto_register(const struct nf_conntrack_l4proto * const l4proto[],
		       unsigned int num_proto)
{
	int ret = -EINVAL, ver;
	unsigned int i;

	for (i = 0; i < num_proto; i++) {
		ret = nf_ct_l4proto_register_one(l4proto[i]);
		if (ret < 0)
			break;
	}
	if (i != num_proto) {
		ver = l4proto[i]->l3proto == PF_INET6 ? 6 : 4;
		pr_err("nf_conntrack_ipv%d: can't register l4 %d proto.\n",
		       ver, l4proto[i]->l4proto);
		nf_ct_l4proto_unregister(l4proto, i);
	}
	return ret;
}
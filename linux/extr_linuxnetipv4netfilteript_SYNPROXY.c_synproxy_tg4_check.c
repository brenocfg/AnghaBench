#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xt_tgchk_param {int /*<<< orphan*/  family; int /*<<< orphan*/  net; struct ipt_entry* entryinfo; } ;
struct synproxy_net {scalar_t__ hook_ref4; } ;
struct TYPE_2__ {scalar_t__ proto; int invflags; } ;
struct ipt_entry {TYPE_1__ ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ IPPROTO_TCP ; 
 int XT_INV_PROTO ; 
 int /*<<< orphan*/  ipv4_synproxy_ops ; 
 int nf_ct_netns_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_netns_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nf_register_net_hooks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct synproxy_net* synproxy_pernet (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int synproxy_tg4_check(const struct xt_tgchk_param *par)
{
	struct synproxy_net *snet = synproxy_pernet(par->net);
	const struct ipt_entry *e = par->entryinfo;
	int err;

	if (e->ip.proto != IPPROTO_TCP ||
	    e->ip.invflags & XT_INV_PROTO)
		return -EINVAL;

	err = nf_ct_netns_get(par->net, par->family);
	if (err)
		return err;

	if (snet->hook_ref4 == 0) {
		err = nf_register_net_hooks(par->net, ipv4_synproxy_ops,
					    ARRAY_SIZE(ipv4_synproxy_ops));
		if (err) {
			nf_ct_netns_put(par->net, par->family);
			return err;
		}
	}

	snet->hook_ref4++;
	return err;
}
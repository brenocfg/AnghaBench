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
struct xt_tgchk_param {int /*<<< orphan*/  family; int /*<<< orphan*/  net; struct ip6t_entry* entryinfo; } ;
struct synproxy_net {scalar_t__ hook_ref6; } ;
struct TYPE_2__ {int flags; scalar_t__ proto; int invflags; } ;
struct ip6t_entry {TYPE_1__ ipv6; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int IP6T_F_PROTO ; 
 scalar_t__ IPPROTO_TCP ; 
 int XT_INV_PROTO ; 
 int /*<<< orphan*/  ipv6_synproxy_ops ; 
 int nf_ct_netns_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_netns_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nf_register_net_hooks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct synproxy_net* synproxy_pernet (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int synproxy_tg6_check(const struct xt_tgchk_param *par)
{
	struct synproxy_net *snet = synproxy_pernet(par->net);
	const struct ip6t_entry *e = par->entryinfo;
	int err;

	if (!(e->ipv6.flags & IP6T_F_PROTO) ||
	    e->ipv6.proto != IPPROTO_TCP ||
	    e->ipv6.invflags & XT_INV_PROTO)
		return -EINVAL;

	err = nf_ct_netns_get(par->net, par->family);
	if (err)
		return err;

	if (snet->hook_ref6 == 0) {
		err = nf_register_net_hooks(par->net, ipv6_synproxy_ops,
					    ARRAY_SIZE(ipv6_synproxy_ops));
		if (err) {
			nf_ct_netns_put(par->net, par->family);
			return err;
		}
	}

	snet->hook_ref6++;
	return err;
}
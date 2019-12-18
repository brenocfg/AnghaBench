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
typedef  int u8 ;
struct nf_hook_entries {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * hooks_ipv6; int /*<<< orphan*/ * hooks_ipv4; int /*<<< orphan*/ * hooks_bridge; } ;
struct net {TYPE_1__ nf; } ;

/* Variables and functions */
#define  NFPROTO_BRIDGE 130 
#define  NFPROTO_IPV4 129 
#define  NFPROTO_IPV6 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct nf_hook_entries* rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nf_hook_entries *nf_hook_entries_head(const struct net *net, u8 pf, u8 hooknum)
{
	switch (pf) {
#ifdef CONFIG_NETFILTER_FAMILY_BRIDGE
	case NFPROTO_BRIDGE:
		return rcu_dereference(net->nf.hooks_bridge[hooknum]);
#endif
	case NFPROTO_IPV4:
		return rcu_dereference(net->nf.hooks_ipv4[hooknum]);
	case NFPROTO_IPV6:
		return rcu_dereference(net->nf.hooks_ipv6[hooknum]);
	default:
		WARN_ON_ONCE(1);
		return NULL;
	}

	return NULL;
}
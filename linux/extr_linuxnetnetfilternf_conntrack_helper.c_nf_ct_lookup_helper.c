#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nf_conntrack_helper {int dummy; } ;
struct nf_conn {TYPE_2__* tuplehash; } ;
struct TYPE_3__ {int auto_assign_helper_warned; int /*<<< orphan*/  sysctl_auto_assign_helper; } ;
struct net {TYPE_1__ ct; } ;
struct TYPE_4__ {int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
 size_t IP_CT_DIR_REPLY ; 
 struct nf_conntrack_helper* __nf_ct_helper_find (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static struct nf_conntrack_helper *
nf_ct_lookup_helper(struct nf_conn *ct, struct net *net)
{
	if (!net->ct.sysctl_auto_assign_helper) {
		if (net->ct.auto_assign_helper_warned)
			return NULL;
		if (!__nf_ct_helper_find(&ct->tuplehash[IP_CT_DIR_REPLY].tuple))
			return NULL;
		pr_info("nf_conntrack: default automatic helper assignment "
			"has been turned off for security reasons and CT-based "
			" firewall rule not found. Use the iptables CT target "
			"to attach helpers instead.\n");
		net->ct.auto_assign_helper_warned = 1;
		return NULL;
	}

	return __nf_ct_helper_find(&ct->tuplehash[IP_CT_DIR_REPLY].tuple);
}
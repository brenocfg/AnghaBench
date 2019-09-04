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
struct TYPE_2__ {int /*<<< orphan*/  proto; } ;
struct sw_flow_key {TYPE_1__ ip; } ;
struct ovs_conntrack_info {scalar_t__ nat; struct nf_conntrack_helper* helper; int /*<<< orphan*/  ct; int /*<<< orphan*/  family; } ;
struct nf_conntrack_helper {int dummy; } ;
struct nf_conn_help {int /*<<< orphan*/  helper; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OVS_NLERR (int,char*,char const*) ; 
 int /*<<< orphan*/  nf_conntrack_helper_put (struct nf_conntrack_helper*) ; 
 struct nf_conntrack_helper* nf_conntrack_helper_try_module_get (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conn_help* nf_ct_helper_ext_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct nf_conntrack_helper*) ; 
 int /*<<< orphan*/  request_module (char*,char const*) ; 

__attribute__((used)) static int ovs_ct_add_helper(struct ovs_conntrack_info *info, const char *name,
			     const struct sw_flow_key *key, bool log)
{
	struct nf_conntrack_helper *helper;
	struct nf_conn_help *help;

	helper = nf_conntrack_helper_try_module_get(name, info->family,
						    key->ip.proto);
	if (!helper) {
		OVS_NLERR(log, "Unknown helper \"%s\"", name);
		return -EINVAL;
	}

	help = nf_ct_helper_ext_add(info->ct, GFP_KERNEL);
	if (!help) {
		nf_conntrack_helper_put(helper);
		return -ENOMEM;
	}

	rcu_assign_pointer(help->helper, helper);
	info->helper = helper;

	if (info->nat)
		request_module("ip_nat_%s", name);

	return 0;
}
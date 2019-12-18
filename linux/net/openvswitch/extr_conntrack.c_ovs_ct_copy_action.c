#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_6__ {int /*<<< orphan*/  proto; } ;
struct sw_flow_key {TYPE_1__ ip; } ;
struct sw_flow_actions {int dummy; } ;
struct ovs_conntrack_info {TYPE_2__* ct; int /*<<< orphan*/  nf_ct_timeout; scalar_t__* timeout; int /*<<< orphan*/  zone; scalar_t__ family; } ;
struct nlattr {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  ct_info ;
struct TYPE_8__ {int /*<<< orphan*/  timeout; } ;
struct TYPE_7__ {int /*<<< orphan*/  ct_general; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IPS_CONFIRMED_BIT ; 
 scalar_t__ NFPROTO_UNSPEC ; 
 int /*<<< orphan*/  NF_CT_DEFAULT_ZONE_DIR ; 
 int /*<<< orphan*/  NF_CT_DEFAULT_ZONE_ID ; 
 int /*<<< orphan*/  OVS_ACTION_ATTR_CT ; 
 int /*<<< orphan*/  OVS_NLERR (int,char*) ; 
 int /*<<< orphan*/  __ovs_ct_free_action (struct ovs_conntrack_info*) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ key_to_nfproto (struct sw_flow_key const*) ; 
 int /*<<< orphan*/  memset (struct ovs_conntrack_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nf_conntrack_get (int /*<<< orphan*/ *) ; 
 scalar_t__ nf_ct_set_timeout (struct net*,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_3__* nf_ct_timeout_find (TYPE_2__*) ; 
 TYPE_2__* nf_ct_tmpl_alloc (struct net*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_zone_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ovs_ct_add_helper (struct ovs_conntrack_info*,char const*,struct sw_flow_key const*,int) ; 
 int ovs_nla_add_action (struct sw_flow_actions**,int /*<<< orphan*/ ,struct ovs_conntrack_info*,int,int) ; 
 int parse_ct (struct nlattr const*,struct ovs_conntrack_info*,char const**,int) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,scalar_t__*) ; 
 int /*<<< orphan*/  rcu_dereference (int /*<<< orphan*/ ) ; 

int ovs_ct_copy_action(struct net *net, const struct nlattr *attr,
		       const struct sw_flow_key *key,
		       struct sw_flow_actions **sfa,  bool log)
{
	struct ovs_conntrack_info ct_info;
	const char *helper = NULL;
	u16 family;
	int err;

	family = key_to_nfproto(key);
	if (family == NFPROTO_UNSPEC) {
		OVS_NLERR(log, "ct family unspecified");
		return -EINVAL;
	}

	memset(&ct_info, 0, sizeof(ct_info));
	ct_info.family = family;

	nf_ct_zone_init(&ct_info.zone, NF_CT_DEFAULT_ZONE_ID,
			NF_CT_DEFAULT_ZONE_DIR, 0);

	err = parse_ct(attr, &ct_info, &helper, log);
	if (err)
		return err;

	/* Set up template for tracking connections in specific zones. */
	ct_info.ct = nf_ct_tmpl_alloc(net, &ct_info.zone, GFP_KERNEL);
	if (!ct_info.ct) {
		OVS_NLERR(log, "Failed to allocate conntrack template");
		return -ENOMEM;
	}

	if (ct_info.timeout[0]) {
		if (nf_ct_set_timeout(net, ct_info.ct, family, key->ip.proto,
				      ct_info.timeout))
			pr_info_ratelimited("Failed to associated timeout "
					    "policy `%s'\n", ct_info.timeout);
		else
			ct_info.nf_ct_timeout = rcu_dereference(
				nf_ct_timeout_find(ct_info.ct)->timeout);

	}

	if (helper) {
		err = ovs_ct_add_helper(&ct_info, helper, key, log);
		if (err)
			goto err_free_ct;
	}

	err = ovs_nla_add_action(sfa, OVS_ACTION_ATTR_CT, &ct_info,
				 sizeof(ct_info), log);
	if (err)
		goto err_free_ct;

	__set_bit(IPS_CONFIRMED_BIT, &ct_info.ct->status);
	nf_conntrack_get(&ct_info.ct->ct_general);
	return 0;
err_free_ct:
	__ovs_ct_free_action(&ct_info);
	return err;
}
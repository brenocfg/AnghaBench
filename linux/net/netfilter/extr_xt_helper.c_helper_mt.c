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
struct xt_helper_info {int invert; char* name; } ;
struct xt_action_param {struct xt_helper_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct nf_conntrack_helper {int /*<<< orphan*/  name; } ;
struct nf_conn_help {int /*<<< orphan*/  helper; } ;
struct nf_conn {int /*<<< orphan*/  master; } ;
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 struct nf_conn* nf_ct_get (struct sk_buff const*,int*) ; 
 struct nf_conn_help* nfct_help (int /*<<< orphan*/ ) ; 
 struct nf_conntrack_helper* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
helper_mt(const struct sk_buff *skb, struct xt_action_param *par)
{
	const struct xt_helper_info *info = par->matchinfo;
	const struct nf_conn *ct;
	const struct nf_conn_help *master_help;
	const struct nf_conntrack_helper *helper;
	enum ip_conntrack_info ctinfo;
	bool ret = info->invert;

	ct = nf_ct_get(skb, &ctinfo);
	if (!ct || !ct->master)
		return ret;

	master_help = nfct_help(ct->master);
	if (!master_help)
		return ret;

	/* rcu_read_lock()ed by nf_hook_thresh */
	helper = rcu_dereference(master_help->helper);
	if (!helper)
		return ret;

	if (info->name[0] == '\0')
		ret = !ret;
	else
		ret ^= !strncmp(helper->name, info->name,
				strlen(helper->name));
	return ret;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct xt_tgchk_param {int /*<<< orphan*/  family; } ;
struct nf_conntrack_helper {int dummy; } ;
struct nf_conn_help {struct nf_conntrack_helper* helper; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  nf_conntrack_helper_put (struct nf_conntrack_helper*) ; 
 struct nf_conntrack_helper* nf_conntrack_helper_try_module_get (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nf_conn_help* nf_ct_helper_ext_add (struct nf_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,...) ; 
 int /*<<< orphan*/  xt_ct_find_proto (struct xt_tgchk_param const*) ; 

__attribute__((used)) static int
xt_ct_set_helper(struct nf_conn *ct, const char *helper_name,
		 const struct xt_tgchk_param *par)
{
	struct nf_conntrack_helper *helper;
	struct nf_conn_help *help;
	u8 proto;

	proto = xt_ct_find_proto(par);
	if (!proto) {
		pr_info_ratelimited("You must specify a L4 protocol and not use inversions on it\n");
		return -ENOENT;
	}

	helper = nf_conntrack_helper_try_module_get(helper_name, par->family,
						    proto);
	if (helper == NULL) {
		pr_info_ratelimited("No such helper \"%s\"\n", helper_name);
		return -ENOENT;
	}

	help = nf_ct_helper_ext_add(ct, GFP_KERNEL);
	if (help == NULL) {
		nf_conntrack_helper_put(helper);
		return -ENOMEM;
	}

	help->helper = helper;
	return 0;
}
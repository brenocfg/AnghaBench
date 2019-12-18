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
struct xt_mtchk_param {int const family; int /*<<< orphan*/  net; struct xt_connlabel_mtinfo* matchinfo; } ;
struct xt_connlabel_mtinfo {int const options; int /*<<< orphan*/  bit; } ;

/* Variables and functions */
 int EINVAL ; 
 int XT_CONNLABEL_OP_INVERT ; 
 int XT_CONNLABEL_OP_SET ; 
 int nf_connlabels_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nf_ct_netns_get (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  nf_ct_netns_put (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int const) ; 

__attribute__((used)) static int connlabel_mt_check(const struct xt_mtchk_param *par)
{
	const int options = XT_CONNLABEL_OP_INVERT |
			    XT_CONNLABEL_OP_SET;
	struct xt_connlabel_mtinfo *info = par->matchinfo;
	int ret;

	if (info->options & ~options) {
		pr_info_ratelimited("Unknown options in mask %x\n",
				    info->options);
		return -EINVAL;
	}

	ret = nf_ct_netns_get(par->net, par->family);
	if (ret < 0) {
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);
		return ret;
	}

	ret = nf_connlabels_get(par->net, info->bit);
	if (ret < 0)
		nf_ct_netns_put(par->net, par->family);
	return ret;
}
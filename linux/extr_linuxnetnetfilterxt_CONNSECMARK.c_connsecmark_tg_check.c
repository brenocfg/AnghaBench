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
struct xt_tgchk_param {int table; int family; int /*<<< orphan*/  net; struct xt_connsecmark_target_info* targinfo; } ;
struct xt_connsecmark_target_info {int mode; } ;

/* Variables and functions */
#define  CONNSECMARK_RESTORE 129 
#define  CONNSECMARK_SAVE 128 
 int EINVAL ; 
 int nf_ct_netns_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int) ; 
 scalar_t__ strcmp (int,char*) ; 

__attribute__((used)) static int connsecmark_tg_check(const struct xt_tgchk_param *par)
{
	const struct xt_connsecmark_target_info *info = par->targinfo;
	int ret;

	if (strcmp(par->table, "mangle") != 0 &&
	    strcmp(par->table, "security") != 0) {
		pr_info_ratelimited("only valid in \'mangle\' or \'security\' table, not \'%s\'\n",
				    par->table);
		return -EINVAL;
	}

	switch (info->mode) {
	case CONNSECMARK_SAVE:
	case CONNSECMARK_RESTORE:
		break;

	default:
		pr_info_ratelimited("invalid mode: %hu\n", info->mode);
		return -EINVAL;
	}

	ret = nf_ct_netns_get(par->net, par->family);
	if (ret < 0)
		pr_info_ratelimited("cannot load conntrack support for proto=%u\n",
				    par->family);
	return ret;
}
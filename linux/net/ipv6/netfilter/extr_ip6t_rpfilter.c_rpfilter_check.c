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
struct xt_rpfilter_info {unsigned int flags; } ;
struct xt_mtchk_param {int /*<<< orphan*/  table; struct xt_rpfilter_info* matchinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int XT_RPFILTER_OPTION_MASK ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rpfilter_check(const struct xt_mtchk_param *par)
{
	const struct xt_rpfilter_info *info = par->matchinfo;
	unsigned int options = ~XT_RPFILTER_OPTION_MASK;

	if (info->flags & options) {
		pr_info_ratelimited("unknown options\n");
		return -EINVAL;
	}

	if (strcmp(par->table, "mangle") != 0 &&
	    strcmp(par->table, "raw") != 0) {
		pr_info_ratelimited("only valid in \'raw\' or \'mangle\' table, not \'%s\'\n",
				    par->table);
		return -EINVAL;
	}

	return 0;
}
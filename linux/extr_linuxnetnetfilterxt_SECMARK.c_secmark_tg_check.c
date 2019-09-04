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
struct xt_tgchk_param {int table; struct xt_secmark_target_info* targinfo; } ;
struct xt_secmark_target_info {int mode; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SECMARK_MODE_SEL 128 
 int checkentry_lsm (struct xt_secmark_target_info*) ; 
 int mode ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,int,...) ; 
 scalar_t__ strcmp (int,char*) ; 

__attribute__((used)) static int secmark_tg_check(const struct xt_tgchk_param *par)
{
	struct xt_secmark_target_info *info = par->targinfo;
	int err;

	if (strcmp(par->table, "mangle") != 0 &&
	    strcmp(par->table, "security") != 0) {
		pr_info_ratelimited("only valid in \'mangle\' or \'security\' table, not \'%s\'\n",
				    par->table);
		return -EINVAL;
	}

	if (mode && mode != info->mode) {
		pr_info_ratelimited("mode already set to %hu cannot mix with rules for mode %hu\n",
				    mode, info->mode);
		return -EINVAL;
	}

	switch (info->mode) {
	case SECMARK_MODE_SEL:
		break;
	default:
		pr_info_ratelimited("invalid mode: %hu\n", info->mode);
		return -EINVAL;
	}

	err = checkentry_lsm(info);
	if (err)
		return err;

	if (!mode)
		mode = info->mode;
	return 0;
}
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
struct xt_tgchk_param {scalar_t__ family; struct xt_log_info* targinfo; } ;
struct xt_log_info {int level; char* prefix; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NFPROTO_IPV4 ; 
 scalar_t__ NFPROTO_IPV6 ; 
 int /*<<< orphan*/  NF_LOG_TYPE_LOG ; 
 int nf_logger_find_get (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 

__attribute__((used)) static int log_tg_check(const struct xt_tgchk_param *par)
{
	const struct xt_log_info *loginfo = par->targinfo;

	if (par->family != NFPROTO_IPV4 && par->family != NFPROTO_IPV6)
		return -EINVAL;

	if (loginfo->level >= 8) {
		pr_debug("level %u >= 8\n", loginfo->level);
		return -EINVAL;
	}

	if (loginfo->prefix[sizeof(loginfo->prefix)-1] != '\0') {
		pr_debug("prefix is not null-terminated\n");
		return -EINVAL;
	}

	return nf_logger_find_get(par->family, NF_LOG_TYPE_LOG);
}
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
struct xt_tgchk_param {struct xt_audit_info* targinfo; } ;
struct xt_audit_info {scalar_t__ type; } ;

/* Variables and functions */
 int ERANGE ; 
 scalar_t__ XT_AUDIT_TYPE_MAX ; 
 int /*<<< orphan*/  pr_info_ratelimited (char*,scalar_t__) ; 

__attribute__((used)) static int audit_tg_check(const struct xt_tgchk_param *par)
{
	const struct xt_audit_info *info = par->targinfo;

	if (info->type > XT_AUDIT_TYPE_MAX) {
		pr_info_ratelimited("Audit type out of range (valid range: 0..%hhu)\n",
				    XT_AUDIT_TYPE_MAX);
		return -ERANGE;
	}

	return 0;
}